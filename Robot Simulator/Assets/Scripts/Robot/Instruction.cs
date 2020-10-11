using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Instruction
{
    public InstructionType InstructionType { get; private set; }
    public float Value { get; private set; }

    public Instruction(InstructionType instruction, float value)
    {
        InstructionType = instruction;
        Value = value;
    }
}
