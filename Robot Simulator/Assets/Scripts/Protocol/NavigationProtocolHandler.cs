using UnityEngine;

public class NavigationProtocolHandler : MonoBehaviour, IProtocolHandler
{
    [SerializeField] private Robot robot;
    public bool HandleInstruction(ProtocolInstruction instruction)
    {

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
                if (instruction.ParameterValues.Length != 1)
                    return false;
                else if (!(instruction.ParameterValues[0]is float))
                    return false;

                robotInstruction = new Instruction(InstructionType.Move, (float)instruction.ParameterValues[0]);
                break;
            case InstructionVariant.BACN:           
                break;
            case InstructionVariant.RIGN:
                break;
            case InstructionVariant.LEFN:
                break;
            case InstructionVariant.TURN:
                break;
                //case InstructionVariant.REQN:
                //    break;
                //case InstructionVariant.NAVS:
                //    break;
                //case InstructionVariant.NAVF:
                break;
            default:
                return false;
        }
        robot.AddInstructions();

        return true;
    }
}
