using UnityEngine;

public class NavigationProtocolHandler : ProtocolHandler
{
    [SerializeField] private Robot robot;

    public override void HandleInstruction(ProtocolInstruction instruction)
    {
        if (robot == null)
        {
            return;
        }

        Instruction robotInstruction = null;
        switch (instruction.Instruction)
        {
            //case InstructionVariant.MOVE:
            //    break;
            //case InstructionVariant.MOVB:
            //    break;
            //case InstructionVariant.MOVT:
            //    break;
            //case InstructionVariant.MOVP:
            //    break;
            //case InstructionVariant.MOVD:
            //    break;
            case InstructionVariant.FORN:
            case InstructionVariant.BACN:
                if (!CheckPermission(instruction, typeof(double)))
                {
                    Debug.LogWarning("Wrong permissions for type");
                    return;
                }

                robotInstruction = new Instruction(InstructionType.Move, (float)((double)instruction.ParameterValues[0]));
                break;
            case InstructionVariant.RIGN:
            case InstructionVariant.LEFN:
                if (!ProtocolHandler.CheckPermission(instruction, typeof(double)))
                {
                    Debug.LogWarning("Wrong permissions for type");
                    return;
                }

                robot.AddInstruction(new Instruction(InstructionType.Rotate, instruction.Instruction == InstructionVariant.LEFN ? -90 : 90));
                robotInstruction = new Instruction(InstructionType.Move, (float)((double)instruction.ParameterValues[0]));
                break;
            case InstructionVariant.TURN:
                if (!ProtocolHandler.CheckPermission(instruction, typeof(double)))
                {
                    Debug.LogWarning("Wrong permissions for type");
                    return;
                }

                robotInstruction = new Instruction(InstructionType.Rotate, (float)((double)instruction.ParameterValues[0]));
                //case InstructionVariant.REQN:
                //    break;
                //case InstructionVariant.NAVS:
                //    break;
                //case InstructionVariant.NAVF:
                break;
            default:
                return;
        }
        robot.AddInstruction(robotInstruction);
    }
}
