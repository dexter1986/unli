using UnityEngine;
using System.Collections;

public class BlinkingLight : MonoBehaviour {

	public Light BlinkLight;
	public float Speed = 3.0f;

	private bool isPrendiendo = true;

	// Use this for initialization
	void Start () {
        BlinkLight.intensity = 0;
	}
	
	// Update is called once per frame
	void Update () {
        if (isPrendiendo)
        {
            BlinkLight.intensity += Time.time;
        }
        else
        {
            BlinkLight.intensity -= Time.time;
        }

        //if (BlinkLight.intensity > 7)
        //{
        //    BlinkLight.intensity = 7;
        //    isPrendiendo = false;
        //}
	}
}
