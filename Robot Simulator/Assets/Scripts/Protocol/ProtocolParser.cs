using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using UnityEngine;

public static class ProtocolParser
{
    public static ProtocolInstruction Parse(string message)
    {
        //Checks for strings with spaces
        const string regexPattern = "[^\\s\"']+|\"([^\"]*)\"|'([^']*)'";
        string[] tokens = Regex.Matches(message, regexPattern).Cast<Match>().Select(m => m.Value).ToArray();

        return HandleData(tokens);
    }

    private static ProtocolInstruction HandleData(IReadOnlyList<string> message)
    {
        const string stringCheck = "\"";

        if (!Enum.TryParse(message[0], out InstructionVariant variant))
            throw new ArgumentException("Invalid variant");


        List<object> objects = new List<object>();

        for (int i = 1; i < message.Count; i++)
        {

            if (message[i].StartsWith(stringCheck) && message[i].EndsWith(stringCheck))
            {
                //Remove " "
                objects.Add(message[i].Substring(1, message.Count - 1));
            }
            else if (double.TryParse(message[i], out double value))
            {
                //Check if it is an integer
                if (value == Math.Floor(value) && !double.IsInfinity(value))
                {
                    int intValue = Convert.ToInt32(value);
                    objects.Add(intValue);
                }
                else
                {
                    objects.Add(value);
                }
            }
            else
            {
                throw new ArgumentException("Invalid parameter");
            }
        }
        return new ProtocolInstruction(variant, objects.ToArray());
    }
}
