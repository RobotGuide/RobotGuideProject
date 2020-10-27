using System.Collections;
using System.Collections.Generic;
using System.Net;
using UnityEngine;

public class AutoConnect : MonoBehaviour
{
    [SerializeField] private string ipAddress = "127.0.0.1";
    [SerializeField] private ushort port = 0;
    private IPAddress address;


    // Start is called before the first frame update
    private void Start()
    {
        if (!IPAddress.TryParse(ipAddress, out address))
        {
            return;
        }

        ClientSocket.Instance.Connect(address, port, OnConnect);
    }


    private void OnConnect(bool connected)
    {
        Debug.Log(connected ? "Connected" : "Failed");
        if (!connected)
        {
            ClientSocket.Instance.Connect(address, port, OnConnect);
        }
    }
}
