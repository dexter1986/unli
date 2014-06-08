package  
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	import net.flashpunk.masks.Pixelmask;
	import net.flashpunk.utils.Key;
	import net.flashpunk.utils.Input;
	import net.flashpunk.Sfx;
	
	/**
	 * ...
	 * @author ...
	 */
	public class Globo extends Entity 
	{
		[Embed(source="BubblePlop.mp3")]
		private	const HIT_SND:Class;		
		private	var	hitSfx:Sfx;
		
		[Embed(source="Globo.png")]
		private const PLAYER_IMG:Class;
		private var playerImage:Image;
		var dir:Number;
		var vely:Number;
		var g:Number = 10;
		var inc_vely = 30;
		var id:Number;
		var isDead:Boolean = false;
		
		public function Globo(px:Number = 0, py:Number = 0) 
		{
			hitSfx = new Sfx(HIT_SND);
			
			playerImage = new Image(PLAYER_IMG);			
			
			super(px, py, playerImage);		
			
			mask = new Pixelmask(PLAYER_IMG);
			type = "Globo";
			
			dir = Math.random() > 0.5 ? 1: -1;
			vely = 0;
			id = Math.random();
		}
		
		override public function update():void
		{
			vely += g * dir *  FP.elapsed;
			y += vely * FP.elapsed;
			
			if (Input.mousePressed)
			{	
				if(this.collidePoint(x,y,Input.mouseX,Input.mouseY))
				{
					if (CenterY() > FP.screen.height / 2)
					{
						vely -= inc_vely;
					}
					else if(CenterY() < FP.screen.height / 2)
					{
						vely += inc_vely;
					}					
				}
			}
			if (isDead && !hitSfx.playing)
			{
				world.remove(this);
			}
		}
		
		public function getWidth():Number
		{
			return playerImage.width;
		}
		
		public function getHeight():Number
		{
			return playerImage.height;
		}
		
		public function CenterY ():Number
		{			
			return y + playerImage.height / 2; 
		}
		
		function Die():void 
		{
			if (!isDead)
			{
				isDead = true;
				hitSfx.play();
			}
		}
	}

}
