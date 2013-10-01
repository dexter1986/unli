using UnityEngine;
using System.Collections;

public class CubeController : MonoBehaviour {

	// Use this for initialization
	void Start () {
		cube = GetComponents<CubeBehaviour>()[0];
	}
	
	CubeBehaviour cube = null;
	
	private bool isRight = false;
	private bool isLeft = false;
	private bool isSpace = false;
		
	// Update is called once per frame
	void Update () {
		if(!isRight && Input.GetKey(KeyCode.RightArrow))
		{
			isRight = true;
			isLeft = isSpace = false;
			cube.State = CubeBehaviour.StateType.RotateRight;
		}
		if(!isLeft && Input.GetKey(KeyCode.LeftArrow))
		{
			isLeft = true;
			isRight = isSpace = false;
			cube.State = CubeBehaviour.StateType.RotateLeft;
		}
		if(!isSpace && Input.GetKey(KeyCode.Space))
		{
			isSpace = true;
			isRight = isLeft = false;
			cube.State = CubeBehaviour.StateType.Stop;
		}
	}	

}
