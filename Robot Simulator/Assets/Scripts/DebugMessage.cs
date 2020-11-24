using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
using UnityEngine;

public class DebugMessage : MonoBehaviour
{
    // Start is called before the first frame update
    private void Start()
    {
        ClientSocket.Instance.OnDataReceived += OnDataReceived;
    }

    private void OnDataReceived(byte[] data, int size)
    {
        Debug.Log(Encoding.ASCII.GetString(data, 0, size));
    }
}
