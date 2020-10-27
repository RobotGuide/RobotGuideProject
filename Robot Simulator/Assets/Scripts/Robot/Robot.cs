using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Robot : MonoBehaviour
{
    [SerializeField] private float speed = 0;
    [SerializeField] private float rotateSpeed = 0;
    private readonly Queue<Instruction> instructions = new Queue<Instruction>();

    private Instruction activeInstruction;

    public void AddInstruction(Instruction instructions)
    {
        this.instructions.Enqueue(instructions);
        CheckForInstruction();
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
        if (instructions.Count <= 0 || activeInstruction != null) return;

        activeInstruction = instructions.Dequeue();
        Vector3 target = CalculateTarget(activeInstruction);
        switch (activeInstruction.InstructionType)
        {
            case InstructionType.Rotate:
                StartCoroutine(Rotate(target, Math.Abs(activeInstruction.Value) / rotateSpeed));
                break;
            case InstructionType.Move:
                StartCoroutine(Move(target, Math.Abs(activeInstruction.Value) / speed));
                break;
            default:
                throw new ArgumentException(nameof(activeInstruction.InstructionType));
        }
    }

    private IEnumerator Rotate(Vector3 target, float time)
    {
        Debug.Log($"Rotate x:{target.x}, y: {target.y}, z: {target.z}");
        WaitForEndOfFrame wait = new WaitForEndOfFrame();
        Quaternion fromAngle = transform.rotation;
        Quaternion toAngle = Quaternion.Euler(target);
        for (float t = 0f; t <= 1.1f; t += Time.deltaTime / time)
        {
            transform.rotation = Quaternion.Lerp(fromAngle, toAngle, t);
            yield return wait;
        }

        activeInstruction = null;
        CheckForInstruction();
    }

    private IEnumerator Move(Vector3 target, float time)
    {
        Debug.Log($"Move x:{target.x}, y: {target.y}, z: {target.z}");
        WaitForEndOfFrame wait = new WaitForEndOfFrame();
        Vector3 position = transform.position;
        for (float t = 0f; t <= 1.1f; t += Time.deltaTime / time)
        {
            transform.position = Vector3.Lerp(position, target, t);
            yield return wait;
        }
        activeInstruction = null;
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
