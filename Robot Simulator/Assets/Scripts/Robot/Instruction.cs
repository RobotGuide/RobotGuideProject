public class Instruction
{
    public InstructionType InstructionType { get; private set; }
    public float Value { get; }

    public Instruction(InstructionType instruction, float value)
    {
        InstructionType = instruction;
        Value = value;
    }
}
