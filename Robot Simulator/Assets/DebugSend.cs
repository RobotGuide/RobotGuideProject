using System.Text;
using UnityEngine;
using UnityEngine.UI;

public class DebugSend : MonoBehaviour
{
    [SerializeField] private Text lastMessage;
    [SerializeField] private InputField input;

    private void Start()
    {
        ClientSocket.Instance.OnDataReceived += OnDataReceived;
    }

    public void Send()
    {
        if (string.IsNullOrWhiteSpace(input.text))
        {
            return;
        }

        ClientSocket.Instance.Send(input.text + '\n');
        input.text = string.Empty;
    }

    private void OnDataReceived(byte[] data, int size)
    {
        lastMessage.text = Encoding.ASCII.GetString(data, 0, size);
    }
}
