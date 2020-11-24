using System;

public class ProtocolInstruction
{
    public InstructionVariant Instruction { get; }
    public object[] ParameterValues { get; }

    public ProtocolInstruction(InstructionVariant instruction, object[] parameterValues)
    {
        Instruction = instruction;
        ParameterValues = parameterValues ?? throw new ArgumentNullException(nameof(parameterValues));
    }
}

public enum InstructionVariant
{
    MOVE,
    LOCA,
    LOCB,
    NAVS,
    NAVF,
    OBSE,
    OBSC,
    REQN,
    MOVB,
    MOVT,
    MOVP,
    MOVD,
    TIMR,
    COMR,
    HEAT,
    HEAS,
    HEAI,
    HEAR,
    FORN,
    BACN,
    RIGN,
    LEFN,
    TURN
}


