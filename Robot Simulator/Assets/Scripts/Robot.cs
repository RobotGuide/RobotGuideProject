using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Robot : MonoBehaviour
{
    [SerializeField] private float speed;
    [SerializeField] private float rotateSpeed;
    private readonly Queue<Instruction> instructions = new Queue<Instruction>();


    private void Start()
    {
        Instruction[] instructions = {new Instruction(InstructionType.Move, 10), 
                                      new Instruction(InstructionType.Rotate, 90),
                                      new Instruction(InstructionType.Move, 10),
                                      new Instruction(InstructionType.Rotate, -90),
                                      new Instruction(InstructionType.Move, 10)};
        AddInstructions(instructions);
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
        CheckForInstruction();
    }

    private void CheckForInstruction()
    {
        if (instructions.Count <= 0) return;

        Instruction currentInstruction = instructions.Dequeue();
        Vector3 target = CalculateTarget(currentInstruction);
        Debug.Log(target);
        switch (currentInstruction.InstructionType)
        {
            case InstructionType.Rotate:
                StartCoroutine(Rotate(target, currentInstruction.Value / rotateSpeed));
                break;
            case InstructionType.Move:
                StartCoroutine(Move(target, currentInstruction.Value / speed));
                break;
            default:
                throw new ArgumentException(nameof(currentInstruction.InstructionType));
        }
    }

    private IEnumerator Rotate(Vector3 target, float time)
    {
        WaitForEndOfFrame wait = new WaitForEndOfFrame();
        Quaternion fromAngle = transform.rotation;
        Quaternion toAngle = Quaternion.Euler(target);
        for (float t = 0f; t <= 1; t += Time.deltaTime / time)
        {
            transform.rotation = Quaternion.Lerp(fromAngle, toAngle, t);
            yield return wait;
        }

        CheckForInstruction();
    }

    private IEnumerator Move(Vector3 target, float time)
    {
        WaitForEndOfFrame wait = new WaitForEndOfFrame();
        Vector3 position = transform.position;
        for (float t = 0f; t <= 1; t += Time.deltaTime / time)
        {
            transform.position = Vector3.Lerp(position, target, t);
            yield return wait;
        }
        CheckForInstruction();
    }


    private Vector3 CalculateTarget(Instruction instruction)
    {
        switch (instruction.InstructionType)
        {
            case InstructionType.Rotate:
                return transform.rotation.eulerAngles + new Vector3(0, instruction.Value, 0);
            case InstructionType.Move:
                return transform.position + transform.forward * instruction.Value;
            default:
                throw new ArgumentException(nameof(instruction.InstructionType));
        }
    }
}
