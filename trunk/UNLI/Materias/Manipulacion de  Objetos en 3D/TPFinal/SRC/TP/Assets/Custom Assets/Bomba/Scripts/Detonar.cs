using UnityEngine;
using System.Collections;

public class Detonar : MonoBehaviour {

    public Cronometro Cronometro;

	// Use this for initialization
	void Start () {
        Cronometro.TimeFinish += Cronometro_TimeFinish;
	}

    void Cronometro_TimeFinish()
    {
        Debug.Log("Boom!");
    }
	
	// Update is called once per frame
	void Update () {
	
	}
}
