package
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	import net.flashpunk.masks.Pixelmask;
	import net.flashpunk.utils.Key;
	import net.flashpunk.utils.Input;
	
	public class Player extends Entity
	{
		[Embed(source="player.png")]
		private const PLAYER_IMG:Class;
		private var playerImage:Image;
		
		public function Player(px:Number = 0, py:Number = 0)
		{
			playerImage = new Image(PLAYER_IMG);
			
			super(px, py, playerImage);
			
			mask = new Pixelmask(PLAYER_IMG);
			type = "Player";
		}
		
		override public function update():void
		{
			if (Input.check(Key.RIGHT))
				if ((this.x + playerImage.width) < FP.screen.width)					
					x += 200 * FP.elapsed;
				else
					this.x = FP.screen.width - playerImage.width;
					
			if (Input.check(Key.LEFT))
				if (this.x > 0)			
					x -= 200 * FP.elapsed;
				else
					this.x = 0;
					
			if (Input.check(Key.DOWN))
				if ((this.y + playerImage.height) < FP.screen.height)					
					y += 200 * FP.elapsed;
				else
					this.y = FP.screen.height - playerImage.height;
					
			if (Input.check(Key.UP))
				if (this.y > 0)					
					y -= 200 * FP.elapsed;
				else
					this.y = 0;
			
			super.update();
		}
		
		public function getWidth():Number
		{
			return playerImage.width;
		}
		
		public function getHeight():Number
		{
			return playerImage.height;
		}
	}
}