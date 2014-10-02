package
{
	import adobe.utils.CustomActions;
	import flash.display.TriangleCulling;
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	import net.flashpunk.masks.Pixelmask;
	import net.flashpunk.utils.Key;
	import net.flashpunk.utils.Input;
	import net.flashpunk.World;
	import net.flashpunk.tweens.misc.VarTween;
	import net.flashpunk.utils.Ease;
	import net.flashpunk.graphics.Text;
	import net.flashpunk.Sfx;
	
	public class GameWorld extends World
	{	
		[Embed(source = "../assets/gfx/music.mp3")] 
		private const snd1:Class;
		public var music:Sfx = new Sfx(snd1);
		
		[Embed(source = "../assets/gfx/music2.mp3")] 
		private const snd2:Class;
		public var music2:Sfx = new Sfx(snd2);
		
		[Embed(source = "../assets/gfx/win.mp3")] 
		private const snd3:Class;
		public var music3:Sfx = new Sfx(snd3);

		[Embed(source="../assets/gfx/FondoFin.png")]
		private const IMG_END:Class;
		public var image_end:Image;	
		
		[Embed(source="../assets/gfx/FondoNormal.png")]
		private const IMG:Class;
		public var image:Image;	
		
		private var status:String;
		private var _player:Player;
		private var moveTween:VarTween;
		private var txtNextAge:Text; 
		private var txtAge:Text; 
		private var txtEtapa:Text; 
		private var txtActividad:Text; 
		private var txtSentimental:Text; 		
		private var txtDinero:Text; 
		private var txtQuiz:Text; 
		private var txtNoQuiz:Text; 		
		private var txtNarrador:Text;
		private var _quiz:Quiz;		
		private var pressText:Text;
		private var pressTweenIn:VarTween;
		private var pressTweenOut:VarTween;
		private var _again:Boolean;
		
		public function GameWorld()
		{
			InitGame();
		}
		
		public function InitGame():void 
		{
			txtNextAge = new Text("---");
			txtNextAge.x = (FP.screen.width / 2) - 25;
			txtNextAge.y = FP.screen.height * 0.70;
			txtNextAge.scale = 2;
			txtNextAge.color = 0x000000;
			
			addGraphic(txtNextAge);			
			
			txtAge = new Text("EDAD: 120");
			txtAge.x = 10;
			txtAge.y = 20;
			txtAge.scale = 1.5;			
			txtAge.color = 0x000000;
			addGraphic(txtAge);
					
			txtEtapa = new Text("----------------------------------------------------------------");
			txtEtapa.x = 10;
			txtEtapa.y = 45;
			txtEtapa.scale = 1.5;			
			txtEtapa.color = 0x000000;
			addGraphic(txtEtapa);
			
			txtActividad = new Text("------------------------------------------------------------");
			txtActividad.x = 10;
			txtActividad.y = 70;
			txtActividad.scale = 1.5;			
			txtActividad.color = 0x000000;
			addGraphic(txtActividad);
			
			txtSentimental = new Text("------------------------------------------------------------");
			txtSentimental.x = 10;
			txtSentimental.y = 95;
			txtSentimental.scale = 1.5;			
			txtSentimental.color = 0x000000;
			addGraphic(txtSentimental);
						
			txtDinero = new Text("DINERO: 100000");
			txtDinero.x = 10;
			txtDinero.y = 120;
			txtDinero.scale = 1.5;			
			txtDinero.color = 0x000000;
			addGraphic(txtDinero);
			
			txtQuiz = new Text("-----------------------------------\n-----------------------------------\n-----------------------------------\n-----------------------------------");
			txtQuiz.x = FP.screen.width *0.3;
			txtQuiz.y = 165;
			txtQuiz.scale = 1.5;			
			txtQuiz.color = 0x000000;
			addGraphic(txtQuiz);
			
			txtNarrador = new Text("-----------------------------------\n-----------------------------------\n-----------------------------------\n-----------------------------------");
			txtNarrador.x = FP.screen.width *0.3;
			txtNarrador.y = 165;
			txtNarrador.scale = 1.5;			
			txtNarrador.color = 0x000000;
			addGraphic(txtNarrador);
			
			this.pressText = new Text("Haz clic para continuar");
			this.pressText.color = 0x000000;
			this.pressText.scale = 1.5;			
			this.pressText.x = FP.screen.width * 0.35;
			this.pressText.y = FP.screen.height * 0.80;
			
			txtNoQuiz = new Text("No es el\nmomento");
			txtNoQuiz.x = FP.screen.width * 0.50;
			txtNoQuiz.y = FP.screen.height * 0.35;
			txtNoQuiz.scale = 1.5;			
			txtNoQuiz.color = 0x000000;
			addGraphic(txtNoQuiz);
			
			pressTweenIn = new VarTween();
			pressTweenOut = new VarTween();
			
			this.addGraphic(pressText);	
			this.addTween(pressTweenIn);
			this.addTween(pressTweenOut);
			
			image_end = new Image(IMG_END);			
			this.addGraphic(image_end);
			
			image = new Image(IMG);			
			this.addGraphic(image);
			
			_player = new Player(0,0);
			add(_player);
			
			_quiz = new Quiz(FP.screen.width * 0.4, FP.screen.height * 0.35);
			add(_quiz);
			
			moveTween = new VarTween();
			addTween(moveTween);
		}
		
		override public function begin():void
		{			
			_again = false;
			image.visible = true;
			image_end.visible = false;
			FP.screen.color = 0xFFFFFF;	
			this.pressText.alpha = 1;
			this.pressText.text = "Haz clic para continuar";
			status = "NORMAL";
			txtQuiz.text = "";
			txtNoQuiz.visible = false;
			txtNarrador.visible = false;
			_player.Initialize();	
			_quiz.Initialize();
			_quiz.SetShow(false);
			ShowNarrador(true);
			PrintNextAge();
			PrintAge();
			music.loop();
		}	
		
		private function SetShowQuiz(value:Boolean,isFinal:Boolean=false):void 
		{
			if (value)
			{
				if(isFinal)
				{
					_quiz.SetFinalQuiz();
				}
				else{
					_quiz.GetRandQuiz(_player.GetEdad(), _player.GetPareja(), _player.GetHijo());							
				}
				txtQuiz.text = _quiz.GetDescription().toUpperCase();		
				_quiz.SetShow(true);
				_quiz.active = true;
				txtNoQuiz.visible = true;			
			}
			else
			{
				txtNoQuiz.visible = false;
				_quiz.active = false;
				_quiz.SetShow(false);
				txtQuiz.text = "";
			}
		}
		
		public function ShowNarrador(value:Boolean,isquiz:Boolean=false):void 
		{
			if (value)
			{
				txtNarrador.visible = true;
				txtNarrador.text = GetNarradorText(isquiz);
			}
			else
			{
				txtNarrador.visible = false;
			}
		}
		
		public function GetNarradorText(isQuiz:Boolean):String 
		{
			if (isQuiz)
			{
				return "QUIZ";
			}
			else
			{
				return "NO_QUIZ";
			}
		}
		
		override public function update():void
		{
			super.update();
			
			switch (status)
			{
				case "NORMAL":
				{
					if (Input.mousePressed)
					{
						ShowNarrador(false);
						status = "MOVE_NEXT";						
						_player.MoveNextStep();							
						moveTween.tween(_player, "x", _player.GetNextPosX(), 1, Ease.backIn);
						pressTweenOut.tween(pressText, "alpha", 0, 0.5);
					}
					break;
				}
				case  "MOVE_NEXT":
				{
					if (moveTween.percent == 1)
					{
						if (_player.GetStep() == 2)
						{
							_player.Grow();
							PrintAge();							
						}
						
						if (_player.GetStep() == -1)
						{
							_player.NextCicle();
							PrintNextAge();
							if (_player.IsEndSoon())
							{
								status = "END_AGE";	
								music.stop();
								music2.loop();
							}
							else
							{
								ShowNarrador(true);
								status = "NORMAL";							
								this.pressText.text = "Haz clic para continuar";
								this.pressText.x = FP.screen.width * 0.35;
							}
						}
						else
						{		
							SetShowQuiz(true);
							if (_quiz.GetTipo() > -1)							{			
								
								status = "QUIZ";
								this.pressText.text = "Elige tu opcion";
								this.pressText.x =  FP.screen.width * 0.40;
							}
							else
							{
								ShowNarrador(true,true);
								SetShowQuiz(false);
								status = "NORMAL";								
								this.pressText.text = "Haz clic para continuar";
								this.pressText.x = FP.screen.width * 0.35;
							}
						}
						
						pressTweenOut.tween(pressText, "alpha", 1, 0.5);
					}
					break;
				}				
				case "QUIZ":
				{
					if (_quiz.OnClick())
					{
						SetShowQuiz(false);
						switch (_quiz.GetTipo()) 
						{
							case 0:
								_player.GotoIglesia(_quiz.GetResult());
							break;
							case 1:
								if (_quiz.GetResult())
								{
									_player.Divertirse();
								}
							break;
							case 2:								
								_player.ReunionFamilia(_quiz.GetResult());
							break;
							case 3:								
								_player.JugarHijos(_quiz.GetResult());
							break;
							case 4:								
								_player.Enamorarse(_quiz.GetResult());
							break;
							case 5:								
								_player.Donacion(_quiz.GetResult());								
							break;
							case 6:								
								_player.Trabajar(_quiz.GetResult());								
							break;
							case 8:								
								if (_quiz.GetResult())
								{
									_player.Infelidad();								
								}
							break;
							case 9:	
								if (_quiz.GetResult())
								{
									_player.Jugar();								
								}
							break;
							default:
						}
					
						SetShowQuiz(false);						
						status = "MOVE_NEXT";
						_player.MoveNextStep();						
						moveTween.tween(_player, "x", _player.GetNextPosX(), 1, Ease.backIn);
						this.pressText.text = "Elige tu opcion";
						pressTweenOut.tween(pressText, "alpha", 0, 0.5);
					}
					break;
				}
				case "END_AGE":
				{
					image.visible = false;
					image_end.visible = true;
					SetShowQuiz(false);
					ShowNarrador(true);
					this.pressText.text = "Haz clic para continuar";
					this.pressText.x = FP.screen.width * 0.25;
					status = "END_AGE_NORMAL";
					break;					
				}
				case "END_AGE_NORMAL":
				{
					if (Input.mousePressed)
					{
						ShowNarrador(false);
						status = "END_AGE_MOVE_NEXT";						
						_player.MoveNextStep();							
						_player.MoveNextStep();
						moveTween.tween(_player, "x", _player.GetNextPosX(), 1, Ease.backIn);
						pressTweenOut.tween(pressText, "alpha", 0, 0.5);
					}					
					break;
				}
				case "END_AGE_MOVE_NEXT":
				{
					if (moveTween.percent == 1)
					{
						SetShowQuiz(true,true);						
						ShowNarrador(false);
						status = "END_AGE_QUIZ";
						this.pressText.text = "Elige tu opcion";
						this.pressText.x =  FP.screen.width * 0.30;
						pressTweenOut.tween(pressText, "alpha", 1, 0.5);
					}
					break;
				}
				case "END_AGE_QUIZ":
				{
					if (_quiz.OnClick())
					{
						SetShowQuiz(false);
						if (_quiz.GetResult())
						{
							status = "END_AGE_CHECK";
							_player.MoveNextStep();
							moveTween.tween(_player, "x", _player.GetNextPosX(), 1, Ease.backIn);
							pressTweenOut.tween(pressText, "alpha", 0, 0.5);
						}
						else
						{
							_again = true;
							this.active = false;
						}
					}
					break;
				}
				case "END_AGE_CHECK":
				{
					if (moveTween.percent == 1)
					{
						_again = false;
						if (_player.EvaluateEspiritu())
						{								
							status = "END_AGE_FINAL_OK1";
							moveTween.tween(_player, "y", FP.screen.height * 0.45,10, Ease.backIn);
						}
						else
						{
							status = "END_AGE_FINAL";
							moveTween.tween(_player.GetSprite(), "alpha", 0, 2);
						}
					}
					break;
				}
				case "END_AGE_FINAL":
				{
					if (moveTween.percent == 1)
					{						
						this.active = false;
					}
					break;
				}
				case "END_AGE_FINAL_OK1":
				{
					if (moveTween.percent == 1)
					{	
						music2.stop();
						music3.loop();
						_player.EvaluteGrowRules();
						status = "END_AGE_FINAL_OK2";
						moveTween.tween(_player, "y", FP.screen.height * 0.35, 12);
					}
					break;
				}
				case "END_AGE_FINAL_OK2":
				{
					if (moveTween.percent == 1)
					{	
						status = "END_AGE_FINAL_OK3";
						moveTween.tween(_player.GetSprite(), "alpha", 0, 3);
					}
					break;
				}
				case "END_AGE_FINAL_OK3":
				{
					if (moveTween.percent == 1)
					{						
						music3.stop();
						this.active = false;
					}
					break;
				}
			}			
		}
		
		public function Again():Boolean
		{
			return _again;
		}
		
		private function PrintNextAge ():void 
		{
			txtNextAge.text = _player.GetNextEdad().toString();
			txtNextAge.x = (FP.screen.width / 2) - txtNextAge.width;
		}
		
		private function PrintAge ():void 
		{
			txtAge.text = "EDAD: " + _player.GetEdad().toString();		
			txtEtapa.text = "ETAPA: " + _player.GetState().toUpperCase();
			txtActividad.text = "ACTIDAD: " + _player.GetActividad();
			txtSentimental.text = "SENTIMENTAL: " + _player.GetSentimental();
			txtDinero.text = "DINERO: " + _player.GetDinero().toString();
		}
	}
}