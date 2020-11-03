using System.Collections;
using System.Collections.Generic;
using System.Net;
using UnityEngine;

public class SearchLocalIP : MonoBehaviour
{
    [SerializeField] private ushort port = 0;
    [SerializeField] private bool startSearchOnStart;

    [SerializeField] private List<IPAddress> possibleAddresses;

    // Start is called before the first frame update
    private void Start()
    {
        if (startSearchOnStart)
        {
            Search();
        }
    }

    public void Search()
    {
#if UNITY_EDITOR
        possibleAddresses = new List<IPAddress>
        {
            IPAddress.Parse("127.0.0.1")
        };
#else
        possibleAddresses = NetworkUtils.GetAllIpAddresses();
#endif
        ConnectNext();
    }

    private void OnConnect(bool connected)
    {
        Debug.Log(connected ? "Connected" : "Failed");
        if (!connected && possibleAddresses.Count > 0)
        {
            ConnectNext();
        }
        else
        {
            Debug.Log("Failed to connect");
        }
    }

    private void ConnectNext()
    {
        ClientSocket.Instance.Connect(possibleAddresses[0], port, OnConnect);
        possibleAddresses.RemoveAt(0);
    }
}
