using UnityEngine;
using System.Collections;

public class MainMenu : MonoBehaviour {

	public GUIStyle StyleText;

	int centerx = 0;
	int centery = 0;

	void OnEnable()
	{
		centerx = Screen.width / 2;
		centery = Screen.height / 2;
		StyleText.fontSize = 28;
		StyleText.normal.textColor = Color.white;
		StyleText.alignment = TextAnchor.MiddleCenter;
	}

	void OnGUI()
	{	
		GUILayout.BeginArea(new Rect(centerx-200,centery-60, 400, 120));
			GUILayout.BeginVertical ();
				GUILayout.Label ("Mi Primer Juego en Unity 3D", StyleText);
				GUILayout.FlexibleSpace ();
				GUILayout.BeginHorizontal();		 
					if(GUILayout.Button("Jugar",GUILayout.Width(100),GUILayout.Height(30))) {			
						}
					GUILayout.FlexibleSpace ();
					if (GUILayout.Button("Configuracion",GUILayout.Width(100),GUILayout.Height(30))) {
							Application.LoadLevel("Settings");
						}
				GUILayout.EndHorizontal ();
				GUILayout.BeginHorizontal();		 
					GUILayout.FlexibleSpace ();
					if (GUILayout.Button ("Acerca de..",GUILayout.Width(100),GUILayout.Height(30))) {
						Application.LoadLevel ("Credits");
					}
					GUILayout.FlexibleSpace ();
				GUILayout.EndHorizontal ();
			GUILayout.EndVertical ();
		GUILayout.EndArea();
	}
}
