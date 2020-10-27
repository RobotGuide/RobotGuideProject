using System.Text;
using UnityEngine;

public class InstructionHandler : MonoBehaviour
{

    [SerializeField] private ProtocolHandler[] handlers;

    // Start is called before the first frame update
    private void Start()
    {
        ClientSocket.Instance.OnDataReceived += OnDataReceived;
    }

    private void OnDataReceived(byte[] data, int size)
    {
        HandleInstructions(ProtocolParser.Parse(Encoding.ASCII.GetString(data, 0, size)));
    }

    private void HandleInstructions(ProtocolInstruction instruction)
    {
        for (int i = 0; i < handlers.Length; i++)
        {
            handlers[i].HandleInstruction(instruction);
        }
    }
}
