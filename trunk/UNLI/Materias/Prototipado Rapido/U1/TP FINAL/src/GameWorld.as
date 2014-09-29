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
		
		protected var status:String;
		private var _player:Player;
		private var moveTween:VarTween;
		
		public function GameWorld()
		{
			InitGame();
		}
		
		public function InitGame():void 
		{
			image = new Image(IMG);			
			this.addGraphic(image);
			
			_player = new Player(0,0);
			add(_player);
			
			moveTween = new VarTween();
			addTween(moveTween);
		}
		
		override public function begin():void
		{
			FP.screen.color = 0xFFFFFF;	
			status = "NORMAL";
			_player.Initialize();
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
						}
						else if (_player.GetStep() == -1)
						{
							_player.NextCicle();
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
		
	}
}