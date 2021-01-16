using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Reset : MonoBehaviour
{
    public void ResetScene()
    {
        ClientSocket.Instance.Reset();
        SceneManager.LoadScene(0);
    }
}
