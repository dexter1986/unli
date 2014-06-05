package  
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	import net.flashpunk.masks.Pixelmask;
		
	public class Solid extends Entity
	{
		[Embed(source="solid.png")]
		private const SOLID_IMG:Class;
		private var solidImg:Image;
		
		private const SCALE = 2.0;
		
		public function Solid(px:Number = 0, py:Number = 0)
		{
			solidImg = new Image(SOLID_IMG);
							
			setHitbox(20 * SCALE, 20 * SCALE);
			width = 20;
			height = 20;
			
			solidImg.scale = SCALE;		
			
			super(px, py, solidImg);
			
			type = "Solid";
		}
	}

}