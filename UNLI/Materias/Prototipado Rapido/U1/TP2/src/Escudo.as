package   
{	
	import flash.geom.Transform;	
	import net.flashpunk.Entity;
	import net.flashpunk.Graphic;
	import net.flashpunk.graphics.Image;	
	import net.flashpunk.utils.Key;
	import net.flashpunk.utils.Input;
	import net.flashpunk.FP;
	import net.flashpunk.utils.Draw;
	
	/**
	 * ...
	 * @author ...
	 */
	public class Escudo extends Entity 
	{
		[Embed(source="escudo.png")]
		private const IMG :Class;
		public var img:Image;
		
		public function Escudo(px:Number=0, py:Number=0) 
		{
			img = new Image(IMG);			
			
			super(px, py, img);			
			
			mask = new TransformPixelmask(IMG);			
			type = "Escudo";						
		}
		
		override public function render():void 
		{			
			//Draw.hitbox(this);
			super.render();
		}
		
		public function Init():void 
		{			
			x += img.width - 20;			
			y -= img.height / 2;		
						
			img.originX = 0;
			img.originY = img.height;			
		}		
		
		override public function update():void 
		{	
			img.angle = FP.angle(x, y, world.mouseX, world.mouseY) * 2;			
			(mask as TransformPixelmask).sync();			
			super.update();
		}
		
	}
}