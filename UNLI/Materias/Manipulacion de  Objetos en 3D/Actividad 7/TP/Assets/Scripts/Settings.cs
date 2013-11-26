using UnityEngine;
using System.Collections;

public class Settings : MonoBehaviour {

	public GUIStyle StyleText;
	
	int centerx = 0;
	int centery = 0;

	bool isSound = true;
	float SoundValue = 50;

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
					GUILayout.BeginHorizontal();				
						isSound = GUILayout.Toggle (isSound,"");
						GUILayout.Label ("Sonido");
						GUILayout.FlexibleSpace ();
					GUILayout.EndHorizontal ();
					GUILayout.BeginHorizontal();	
						GUILayout.BeginVertical ();						
							if (isSound) {																	
								GUILayout.Label ("Volumen");
								SoundValue = GUILayout.HorizontalSlider (SoundValue, 0, 100);									
							} else {
								GUILayout.Label ("");
								GUILayout.Label ("");
							}
						GUILayout.EndVertical ();
					GUILayout.EndHorizontal ();
					GUILayout.ExpandHeight(!isSound);
				GUILayout.EndVertical ();
			GUILayout.EndHorizontal ();
		GUILayout.EndArea();
	}
}
