using UnityEngine;
using System.Collections;

public class CubeBehaviour : MonoBehaviour {
		
	public enum StateType
	{
		RotateLeft,
		RotateRight,
		Stop
	}
		
	public StateType State = StateType.Stop;
	
	public float degreesPerSecond = 45.0f;
	
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {		
		switch(State)
		{
			case StateType.RotateLeft:				
				transform.Rotate(0,degreesPerSecond * Time.deltaTime,0);
				break;
			case StateType.RotateRight:
				transform.Rotate(0,-degreesPerSecond * Time.deltaTime,0);
				break;
			case StateType.Stop:
				break;			
		}
	}
}
