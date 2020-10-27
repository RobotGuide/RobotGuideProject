using System;
using System.Linq;
using UnityEngine;

public abstract  class ProtocolHandler : MonoBehaviour
{
   public  abstract void HandleInstruction(ProtocolInstruction instruction);

       /// <summary>
    /// Check if permissions are valid for this type
    /// </summary>
    /// <param name="instruction">The instructions received</param>
    /// <param name="types">The types the parameter must be</param>
    /// <returns></returns>
    public static bool CheckPermission(ProtocolInstruction instruction, params Type[] types)
    {
        if (instruction.ParameterValues.Length > types.Length)
            return false;

        return !types.Where((t, i) => instruction.ParameterValues[i].GetType() != t).Any();
    }
}

 