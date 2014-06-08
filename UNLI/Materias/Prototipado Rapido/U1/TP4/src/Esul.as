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
	public class Esul extends Entity 
	{
		[Embed(source="EstacasSuelo.png")]
		private const ESUL_IMG:Class;
		private var esulimg:Image;
		
		public function Esul(px:Number = 0, py:Number = 0) 
		{
			esulimg = new Image(ESUL_IMG);			
			
			super(px, py, esulimg);		
			
			mask = new Pixelmask(ESUL_IMG);
			type = "Esul";
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
			return esulimg.width;
		}
		
		public function getHeight():Number
		{
			return esulimg.height;
		}
		
	}

}