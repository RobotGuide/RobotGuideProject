using System;
using System.Net.Sockets;
using System.Net;
using UnityEngine;
using System.Text;

[RequireComponent(typeof(Dispatcher))]
public class ClientSocket : MonoBehaviour
{
    /// <summary>
    /// Get the singleton instance
    /// </summary>
    public static ClientSocket Instance { get; private set; }

    /// <summary>
    /// Check if the Client Socket is connected
    /// </summary>
    public bool IsConnected => tcpClient != null && tcpClient.Connected;

    /// <summary>
    /// Add or remove the event
    /// </summary>
    public event Action<byte[], int> OnDataReceived
    {
        add => DataReceived += value;
        remove => DataReceived -= value;
    }
    private event Action<byte[], int> DataReceived;


    private Socket tcpClient;
    private byte[] buffer;

    /// <summary>
    /// Activate the Singleton
    /// </summary>
    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(this);
        }
        else
        {
            Destroy(this);
        }
    }

    /// <summary>
    /// Try to connect with a specific ip address
    /// </summary>
    /// <param name="ip">The ip address you want to connect to</param>
    /// <param name="port">The port you want to use</param>
    /// <param name="connectCallback">The callback for when it is connected</param>
    /// <param name="socket">The socket you want to use</param>
    /// <param name="bufferSize">The size of the buffer for this connection</param>
    /// /// <exception cref="InvalidOperationException"/>
    /// <exception cref="ArgumentNullException">Socket, connectCallback and ip can not be null</exception>
    public void Connect(IPAddress ip, ushort port, Action<bool> connectCallback, Socket socket, uint bufferSize = 1024)
    {
        if (ip == null) throw new ArgumentNullException(nameof(ip));
        if (connectCallback == null) throw new ArgumentNullException(nameof(connectCallback));
        if (socket == null) throw new ArgumentNullException(nameof(socket));
        if (connectCallback == null) throw new ArgumentNullException(nameof(connectCallback));

        if (IsConnected)
        {
            throw new InvalidOperationException("TCP client is already connected");
        }

        buffer = new byte[bufferSize];
        _ = socket.BeginConnect(ip, port, EndConnect, new ConnectionData(socket, connectCallback));
    }


    /// <summary>
    /// Try to connect with a specific ip address
    /// </summary>
    /// <param name="ip">The ip address you want to connect to</param>
    /// <param name="port">The port you want to use</param>
    /// <param name="connectCallback">The callback for when it is connected</param>
    /// <param name="bufferSize">The size of the buffer for this connection</param>
    /// <param name="addressFamily">The address family</param>
    /// <param name="socketType">The type of socket</param>
    /// <param name="protocolType">The protocol type</param>
    /// <exception cref="InvalidOperationException"/>
    /// <exception cref="ArgumentNullException"/>
    public void Connect(IPAddress ip, ushort port, Action<bool> connectCallback, uint bufferSize = 1024,
        AddressFamily addressFamily = AddressFamily.InterNetwork, SocketType socketType = SocketType.Stream,
        ProtocolType protocolType = ProtocolType.Tcp)
    {
        Connect(ip, port, connectCallback, new Socket(addressFamily, socketType, protocolType), bufferSize);
    }

    /// <summary>
    /// Disconnect the Client Socket
    /// </summary>
    public void Disconnect()
    {
        tcpClient?.Close();
        DataReceived = null;
        tcpClient = null;
    }

    /// <summary>
    /// Send a message on the socket
    /// </summary>
    /// <param name="message">The message you want to send</param>
    public void Send(string message)
    {
        tcpClient?.Send(Encoding.ASCII.GetBytes(message));
    }

    /// <summary>
    /// Set a new buffer size
    /// </summary>
    /// <param name="bufferSize">The size of the new buffer</param>
    public void ChangeBufferSize(uint bufferSize)
    {
        buffer = new byte[bufferSize];
    }

    /// <summary>
    /// Handle connection
    /// </summary>
    /// <param name="result">The result for the async result</param>
    private void EndConnect(IAsyncResult result)
    {
        if (result == null) throw new ArgumentNullException(nameof(result));

        if (IsConnected)
        {
            return;
        }

        ConnectionData data = (ConnectionData)result.AsyncState;
        try
        {
            data.Socket.EndConnect(result);
            tcpClient = data.Socket;
        }
        catch (SocketException e)
        {
            Debug.LogError(e);
        }
        catch (ObjectDisposedException e)
        {
            Debug.LogError(e);
        }

        if (Dispatcher.Instance != null)
            Dispatcher.Instance.Invoke(() => data.CallBack(IsConnected));

        if (IsConnected)
        {
            BeginReceive();
        }
    }

    /// <summary>
    /// Setup the callback for receiving data
    /// </summary>
    private void BeginReceive()
    {
        if (!IsConnected)
        {
            return;
        }
        tcpClient.BeginReceive(buffer, 0, buffer.Length, 0, ReadCallback, tcpClient);
    }

    /// <summary>
    /// Read the callback for receiving data
    /// </summary>
    /// <param name="ar">The synchronous result</param>
    private void ReadCallback(IAsyncResult ar)
    {
        if (ar == null) throw new ArgumentNullException(nameof(ar));


        int bytesRead = tcpClient.EndReceive(ar);
        if (bytesRead > 0)
        {

            if (Dispatcher.Instance != null)
                Dispatcher.Instance.Invoke(() => DataReceived?.Invoke(buffer, bytesRead));
            BeginReceive();
        }
        else
        {
            Debug.Log("Disconnected from server");
            Disconnect();
        }
    }
}