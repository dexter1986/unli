using UnityEngine;
using System.Collections;
using Tools;

public class Cronometro : MonoBehaviour
{
    public event ActionEvent TimeFinish;

    public bool IsAscendente = false;
    public int MinValue = 0;
    public int MaxValue = 120;
    public int Value = 0;
    public TextMesh Text;
    
    private int PadLeft = 0;

	// Use this for initialization
	void Start () {
        PadLeft = MaxValue.ToString().Length;
        StartCoroutine(Contador());
	}
	
	// Update is called once per frame
	void Update () {            
	}

    IEnumerator Contador()
    {        
        if(IsAscendente)
        {
            Value = MinValue;
        }else
        {
            Value = MaxValue;
        }        
        while (true)
        {
            Text.text = Value.ToString().PadLeft(PadLeft, '0');
            yield return new WaitForSeconds(1);
            if (IsAscendente)
            {
                Value++;                
            }
            else
            {
                Value--;
            }
            if (Value > MaxValue || Value < MinValue)
            {
                break;
            }            
        }
        //Lanzar Evento
        if (TimeFinish != null)
        {
            TimeFinish();
        }
    }
}
