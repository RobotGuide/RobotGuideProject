using UnityEngine;

public class InitializationProtocolHandler : ProtocolHandler
{
    private const int InvalidId = -1;
    [SerializeField] private int robotID = InvalidId;

    public override void HandleInstruction(ProtocolInstruction instruction)
    {
        switch (instruction.Instruction)
        {
            case InstructionVariant.ASKI:
                if (!CheckPermission(instruction, typeof(int)))
                    return;
                ClientSocket.Instance.Send(robotID == InvalidId ? "SENI 0\n" : $"SENI 0 {robotID}\n");
                break;

            case InstructionVariant.SETI:
                if (!CheckPermission(instruction, typeof(int), typeof(int)))
                    return;
                robotID = (int)instruction.ParameterValues[1];
                break;
        }
    }
}
