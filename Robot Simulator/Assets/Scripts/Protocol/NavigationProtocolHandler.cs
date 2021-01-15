using System;
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
            case InstructionVariant.FORN:
            case InstructionVariant.BACN:
                if (!CheckPermission(instruction, typeof(double)) &&
                    !CheckPermission(instruction, typeof(int)))
                {
                    Debug.LogWarning("Wrong permissions for type");
                    return;
                }
                double value = Convert.ToDouble(instruction.ParameterValues[0]);
                if (instruction.Instruction == InstructionVariant.BACN)
                    value = -value;

                robotInstruction = new Instruction(InstructionType.Move, (float)(value / 1000));
                break;
            case InstructionVariant.RIGN:
            case InstructionVariant.LEFN:
                if (!CheckPermission(instruction, typeof(double)) &&
                    !CheckPermission(instruction, typeof(int)))
                {
                    Debug.LogWarning("Wrong permissions for type");
                    return;
                }

                robot.AddInstruction(new Instruction(InstructionType.Rotate, instruction.Instruction == InstructionVariant.LEFN ? -90 : 90));
                robotInstruction = new Instruction(InstructionType.Move, ((float)instruction.ParameterValues[0]) / 1000);
                break;
            case InstructionVariant.TURN:
                if (!CheckPermission(instruction, typeof(double)) &&
                    !CheckPermission(instruction, typeof(int)))
                {
                    Debug.LogWarning("Wrong permissions for type");
                    return;
                }

                robotInstruction = new Instruction(InstructionType.Rotate, ((float)instruction.ParameterValues[0]) / 1000);
                break;
            default:
                return;
        }
        robot.AddInstruction(robotInstruction);
    }
}
