using System;
using System.Collections.Generic;
using System.Numerics;
using UnityEngine;
using Quaternion = UnityEngine.Quaternion;
using Vector3 = UnityEngine.Vector3;

public class Robot : MonoBehaviour
{
    [SerializeField] private float speed;
    [SerializeField] private float rotateSpeed;
    private readonly Queue<Instruction> instructions = new Queue<Instruction>();

    private Instruction currentInstruction;
    private Vector3 target;

    private Vector3 startPosition;
    private Quaternion startRotation;

    private void Start()
    {
        instructions.Enqueue(new Instruction(InstructionType.Move, 10));
        instructions.Enqueue(new Instruction(InstructionType.Rotate, 90));
        instructions.Enqueue(new Instruction(InstructionType.Move, 10));
        instructions.Enqueue(new Instruction(InstructionType.Rotate, -90));
    }

    private void Update()
    {
        CheckForInstruction();
        if (currentInstruction == null)
        {
            return;
        }
        if (currentInstruction.InstructionType == InstructionType.Move)
        {
            transform.position = Vector3.Slerp(transform.position, target, speed * Time.deltaTime);
            if (Vector3.Distance(transform.position, target) < .1f)
            {
                currentInstruction = null;
            }
        }
        else
        {
            transform.rotation = Quaternion.Slerp(transform.rotation, Quaternion.Euler(target), rotateSpeed * Time.deltaTime);
            if (transform.rotation.eulerAngles == target)
            {
                currentInstruction = null;
            }
        }
    }

    private void CheckForInstruction()
    {
        if (instructions.Count > 0 && currentInstruction == null)
        {
            currentInstruction = instructions.Dequeue();
            target = CalculateTarget(currentInstruction);
            Debug.Log(target);
            switch (currentInstruction.InstructionType)
            {
                case InstructionType.Rotate:
                    startPosition = transform.position;
                    break;
                case InstructionType.Move:
                    startRotation = transform.rotation;
                    break;
                default:
                    throw new ArgumentException(nameof(currentInstruction.InstructionType));
            }
        }
    }

    private Vector3 CalculateTarget(Instruction instruction)
    {
        switch (instruction.InstructionType)
        {
            case InstructionType.Rotate:
                return transform.rotation.eulerAngles - new Vector3(0, instruction.Value, 0);
            case InstructionType.Move:
                return transform.position + transform.forward * instruction.Value;
            default:
                throw new ArgumentException(nameof(instruction.InstructionType));
        }
    }

    public void AddInstructions(Instruction[] instructions)
    {
        for (int i = 0; i < instructions.Length; i++)
        {
            if (instructions[i] != null)
            {
                this.instructions.Enqueue(instructions[i]);
            }
        }

    }
}
