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
	
	public class GameEnd extends World
	{	
		[Embed(source="../assets/gfx/FondoFin.png")]
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
		private var _quiz:Quiz;
		
		public function GameEnd()
		{
			InitGame();
		}
		
		public function InitGame():void 
		{
			txtNextAge = new Text("---");
			txtNextAge.x = (FP.screen.width / 2) - 25;
			txtNextAge.y = FP.screen.height * 0.70;
			txtNextAge.scale = 1.2;// 2;
			txtNextAge.color = 0x000000;
			
			addGraphic(txtNextAge);			
			
			txtAge = new Text("EDAD: 120");
			txtAge.x = 10;
			txtAge.y = 20;
			txtAge.scale = 1.2;// 1.5;			
			txtAge.color = 0x000000;
			addGraphic(txtAge);
					
			txtEtapa = new Text("-----------------------");
			txtEtapa.x = 10;
			txtEtapa.y = 45;
			txtEtapa.scale = 1.2;// 1.5;			
			txtEtapa.color = 0x000000;
			addGraphic(txtEtapa);
			
			txtActividad = new Text("------------------------------------------------------------");
			txtActividad.x = 10;
			txtActividad.y = 70;
			txtActividad.scale = 1.2;// 1.5;			
			txtActividad.color = 0x000000;
			addGraphic(txtActividad);
			
			txtSentimental = new Text("-----------------------");
			txtSentimental.x = 10;
			txtSentimental.y = 95;
			txtSentimental.scale = 1.2;// 1.5;			
			txtSentimental.color = 0x000000;
			addGraphic(txtSentimental);
						
			txtDinero = new Text("DINERO: 100000");
			txtDinero.x = 10;
			txtDinero.y = 120;
			txtDinero.scale = 1.2;// 1.5;			
			txtDinero.color = 0x000000;
			addGraphic(txtDinero);
			
			image = new Image(IMG);			
			this.addGraphic(image);
			
			_player = new Player(0,0);
			add(_player);
			
			_quiz = new Quiz(FP.screen.width * 0.5 - 30, FP.screen.height * 0.3);
			add(_quiz);
			
			moveTween = new VarTween();
			addTween(moveTween);
		}
		
		override public function begin():void
		{
			FP.screen.color = 0xFFFFFF;	
			status = "NORMAL";
			_player.Initialize();	
			_quiz.Initialize();
			PrintNextAge();
			PrintAge();
		}		
		
		override public function update():void
		{
			switch (status)
			{
				case "NORMAL":
				{
					if (Input.mousePressed)
					{
						status = "MOVE_NEXT";
						_player.MoveNextStep();
						moveTween.tween(_player, "x", _player.GetNextPosX(), 1, Ease.backIn);
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
						else if (_player.GetStep() == -1)
						{
							_player.NextCicle();
							PrintNextAge();
							if (_player.IsEndSoon())
							{
								
							}							
						}
						status = "NORMAL";
					}
				}
				break;
				case "QUIZ":
				{
					
					break;
				}
			}
			
			super.update();
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