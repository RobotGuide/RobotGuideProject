using System;
using System.Text;
using UnityEngine;

public class InstructionHandler : MonoBehaviour
{
    [SerializeField] private ProtocolHandler[] handlers;

    // Start is called before the first frame update
    private void Awake()
    {
        ClientSocket.Instance.OnDataReceived += OnDataReceived;
    }

    private void OnDataReceived(byte[] data, int size)
    {
        string message = Encoding.ASCII.GetString(data, 0, size);
        foreach (string instruction in message.Split('\n'))
        {
            if (!string.IsNullOrWhiteSpace(instruction))
            {
                HandleInstructions(ProtocolParser.Parse(instruction));
            }
        }
    }

    private void HandleInstructions(ProtocolInstruction instruction)
    {
        foreach (ProtocolHandler handler in handlers)
        {
            handler.HandleInstruction(instruction);
        }
    }
}
