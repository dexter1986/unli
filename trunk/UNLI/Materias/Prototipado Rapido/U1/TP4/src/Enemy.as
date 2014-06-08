package  
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	import net.flashpunk.masks.Pixelmask;
	
	/**
	 * ...
	 * @author Acid
	 */
	public class Enemy extends Entity
	{
		[Embed(source="enemy.png")]
		private const ENEMY_IMG:Class;
		private var enemyImg:Image;
		
		public function Enemy(px:Number = 0, py:Number = 0)
		{
			enemyImg = new Image(ENEMY_IMG);
			enemyImg.color = 0xDD0000;
			
			mask = new Pixelmask(ENEMY_IMG);
			
			type = "Enemy";
			
			super(px, py, enemyImg);
		}
		
		override public function update():void
		{			
			y += 200 * FP.elapsed;
			
			if (y > FP.screen.height)
				world.remove(this);
				
			if (this.collide("Player", this.x, this.y))
				FP.world = new GameWorld();
		}
	}

}