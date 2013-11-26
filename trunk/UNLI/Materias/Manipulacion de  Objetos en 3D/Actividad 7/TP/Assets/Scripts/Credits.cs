using UnityEngine;
using System.Collections;

public class Credits : MonoBehaviour {

	public GUIStyle StyleText;
	
	int centerx = 0;
	int centery = 0;

	void OnEnable()
	{
		centerx = Screen.width / 2;
		centery = Screen.height / 2;
		StyleText.fontSize = 18;
		StyleText.normal.textColor = Color.white;
		StyleText.alignment = TextAnchor.MiddleCenter;
	}

	void OnGUI()
	{	
		GUILayout.BeginArea(new Rect(centerx-200,centery-60, 400, 120));
			GUILayout.BeginHorizontal();	
				GUILayout.BeginVertical ();
					GUILayout.FlexibleSpace ();
					if (GUILayout.Button ("<< Volver",GUILayout.Width(100),GUILayout.Height(30))) {
						Application.LoadLevel ("MainMenu");
					}
				GUILayout.EndVertical ();
				GUILayout.BeginVertical ();			
					GUILayout.FlexibleSpace ();
					GUILayout.Label ("Mi Primer Juego en Unity 3D", StyleText);				
					GUILayout.FlexibleSpace ();
					GUILayout.Label ("Oscar Sanchez", StyleText);	
					GUILayout.FlexibleSpace ();
					GUILayout.Label ("Comision", StyleText);	
					GUILayout.FlexibleSpace ();
					GUILayout.Label ("2013", StyleText);	
					GUILayout.FlexibleSpace ();
				GUILayout.EndVertical ();
			GUILayout.EndHorizontal ();
		GUILayout.EndArea();
	}
}
