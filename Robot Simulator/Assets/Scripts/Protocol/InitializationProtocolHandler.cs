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
                if (!CheckPermission(instruction))
                    return;
                ClientSocket.Instance.Send(robotID == InvalidId ? "SENI 0" : $"SENI 0 {robotID}");
                break;

            case InstructionVariant.SETI:
                if (!CheckPermission(instruction, typeof(int)))
                    return;
                robotID = (int)instruction.ParameterValues[0];
                break;
        }
    }
}
