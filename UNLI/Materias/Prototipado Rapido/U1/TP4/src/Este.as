package  
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	import net.flashpunk.masks.Pixelmask;
	import net.flashpunk.utils.Key;
	import net.flashpunk.utils.Input;
	
	/**
	 * ...
	 * @author ...
	 */
	public class Este extends Entity 
	{
		[Embed(source="EstacasTecho.png")]
		private const ESTE_IMG:Class;
		private var esteimg:Image;
			
		public function Este(px:Number = 0, py:Number = 0) 
		{
			esteimg = new Image(ESTE_IMG);	
			
			super(px, py, esteimg);		
			
			mask = new Pixelmask(ESTE_IMG);
			type = "Este";
		}
		
		override public function update():void
		{
			var a:Globo = this.collide("Globo", this.x, this.y) as Globo;
			if (a)			
			{
				a.Die();
			}
		}
		
		public function getWidth():Number
		{
			return esteimg.width;
		}
		
		public function getHeight():Number
		{
			return esteimg.height;
		}
		
	}

}