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
    public event Action<string> OnMessageReceived {
        add => MessageReceived += value;
        remove => MessageReceived -= value;
    }
    private event Action<string> MessageReceived;


    private Socket tcpClient = null;
    private readonly byte[] buffer = new byte[1024];

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
    /// Try to connect with select ip address
    /// </summary>
    /// <param name="ip">The ip address you want to connect to</param>
    /// <param name="port">The port you want to use</param>
    /// <param name="connectCallback">The callback for when it is connected</param>
    public void StartConnect(IPAddress ip, ushort port, Action<bool> connectCallback)
    {
        if (ip == null) throw new ArgumentNullException(nameof(ip));
        if (connectCallback == null) throw new ArgumentNullException(nameof(connectCallback));

        if (tcpClient != null)
        {
            throw new InvalidOperationException("TCP client is already connected");
        }

        Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);


        _ = socket.BeginConnect(ip, port, EndConnect, new ConnectionData(socket, connectCallback));
    }

    /// <summary>
    /// Disconnect the Client Socket
    /// </summary>
    public void Disconnect()
    {
        tcpClient?.Close();
        MessageReceived = null;
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
    /// Handle connection
    /// </summary>
    /// <param name="result">The result for the async result</param>
    private void EndConnect( IAsyncResult result)
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

        Dispatcher.Instance?.Invoke(() => data.CallBack(IsConnected));

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
            string message = Encoding.ASCII.GetString(buffer, 0, bytesRead);
            Dispatcher.Instance?.Invoke(() => MessageReceived?.Invoke(message));
            BeginReceive();
        }
        else
        {
            Debug.Log("Disconnected from server");
            Disconnect();
        }
    }
}