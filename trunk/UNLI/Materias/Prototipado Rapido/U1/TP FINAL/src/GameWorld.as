package
{
	import adobe.utils.CustomActions;
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
	
	public class GameWorld extends World
	{	
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
		private var _quiz:Quiz;		
		protected var pressText:Text;
		private var pressTweenIn:VarTween;
		private var pressTweenOut:VarTween;
		
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
			
			this.pressText = new Text("Haz clic para continuar");
			this.pressText.color = 0x000000;
			this.pressText.scale = 1.5;			
			this.pressText.x = FP.screen.width * 0.35;
			this.pressText.y = FP.screen.height * 0.80;
			
			pressTweenIn = new VarTween();
			pressTweenOut = new VarTween();
			
			this.addGraphic(pressText);	
			this.addTween(pressTweenIn);
			this.addTween(pressTweenOut);
			
			image = new Image(IMG);			
			this.addGraphic(image);
			
			_player = new Player(0,0);
			add(_player);
			
			_quiz = new Quiz(FP.screen.width * 0.45, FP.screen.height * 0.35);
			add(_quiz);
			
			moveTween = new VarTween();
			addTween(moveTween);
		}
		
		override public function begin():void
		{
			FP.screen.color = 0xFFFFFF;	
			this.pressText.alpha = 1;
			this.pressText.text = "Haz clic para continuar";
			status = "NORMAL";
			txtQuiz.text = "";
			_player.Initialize();	
			_quiz.Initialize();
			_quiz.SetShow(false);
			PrintNextAge();
			PrintAge();
		}	
		
		private function SetShowQuiz(value:Boolean):void 
		{
			if (value)
			{
				_quiz.GetRandQuiz(_player.GetEdad(), _player.GetPareja(), _player.GetHijo());							
				txtQuiz.text = _quiz.GetDescription().toUpperCase();		
				_quiz.SetShow(true);
				_quiz.active = true;
			}
			else
			{
				_quiz.active = false;
				_quiz.SetShow(false);
				txtQuiz.text = "";
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
								active = false;
							}			
							status = "NORMAL";
							this.pressText.text = "Haz clic para continuar";
							this.pressText.x = FP.screen.width * 0.35;
						}
						else
						{	
							SetShowQuiz(true);
							if (_quiz.GetTipo() > -1)
							{
								
								status = "QUIZ";
								this.pressText.text = "Elige tu opcion";
								this.pressText.x =  FP.screen.width * 0.40;
							}
							else
							{
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
			}
			
			
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