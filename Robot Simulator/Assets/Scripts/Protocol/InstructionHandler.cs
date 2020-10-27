using System.Collections;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

public class InstructionHandler : MonoBehaviour
{
    // Start is called before the first frame update
    private void Start()
    {
        ClientSocket.Instance.OnDataReceived += OnDataReceived;
    }

    private void OnDataReceived(byte[] data, int size)
    {
        ProtocolParser.Parse(Encoding.ASCII.GetString(data, 0, size));
    }

    private void HandleInstructions(ProtocolInstruction instruction)
    {

    }
}
