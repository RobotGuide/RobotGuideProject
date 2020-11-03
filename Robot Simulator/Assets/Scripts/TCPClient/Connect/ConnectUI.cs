using System.Net;
using UnityEngine;
using UnityEngine.UI;

public class ConnectUI : MonoBehaviour
{
    [SerializeField] private Canvas panelUI;
    [SerializeField] private InputField ipInput;
    [SerializeField] private InputField portInput;
    [SerializeField] private Text errorText;

    private void Update()
    {
        if (!panelUI.isActiveAndEnabled && ClientSocket.Instance != null && !ClientSocket.Instance.IsConnected)
        {
            panelUI.enabled = true;
        }
        else if (panelUI.isActiveAndEnabled && ClientSocket.Instance != null && ClientSocket.Instance.IsConnected)
        {
            panelUI.enabled = false;
        }
    }

    public void Connect()
    {
        if (ClientSocket.Instance == null || ClientSocket.Instance.IsConnected)
        {
            if (errorText != null)
            {
                errorText.text = "No Client socket exists in the scene";
            }
            return;
        }

        if (!IPAddress.TryParse(ipInput.text, out IPAddress ipAddress))
        {
            if (errorText != null)
            {
                errorText.text = "IP Address is invalid";
            }
            return;
        }

        if (!ushort.TryParse(portInput.text, out ushort port) || port > 65535)
        {
            if (errorText != null)
            {
                errorText.text = "port is invalid";
            }
            return;
        }
        if (errorText != null)
        {
            errorText.text = "Connecting please wait";
        }
        ClientSocket.Instance.Connect(ipAddress, port, OnConnect);
    }

    private void OnConnect(bool connected)
    {
        panelUI.enabled = connected;
        errorText.text = $"Socket is {(connected ? "connected" : "not connected")}";

    }


}
