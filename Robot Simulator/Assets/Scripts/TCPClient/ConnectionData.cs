using System;
using System.Net.Sockets;

internal readonly struct ConnectionData
{
    public Action<bool> CallBack { get; }
    public Socket Socket { get; }

    public ConnectionData(Socket socket, Action<bool> callBack)
    {
        Socket = socket ?? throw new ArgumentNullException(nameof(socket));
        CallBack = callBack ?? throw new ArgumentNullException(nameof(callBack));
    }

}