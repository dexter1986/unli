package
{
	import net.flashpunk.World;
	import net.flashpunk.FP;
	
	public class GameWorld extends World
	{
		protected var player:Personaje;
		
		public function GameWorld()
		{
			this.player = new Personaje(FP.screen.width / 2, FP.screen.height / 2);
			
			this.add(player);
		}
		
		override public function update():void
		{
			/*
			if (classCount(Enemy) < 10)
				for (var i:uint = 0; i < 10; i++)
					this.add(new Enemy(FP.rand(FP.screen.width - player.getWidth()), -(FP.rand(400) - player.getHeight())));
		    */
			super.update();
		}
	}
}