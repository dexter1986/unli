package   
{
	import adobe.utils.CustomActions;
	import flash.display.BitmapData;
	import flash.sampler.NewObjectSample;
	import net.flashpunk.Entity;
	import net.flashpunk.Graphic;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.masks.Pixelmask;
	import net.flashpunk.Sfx;
	import net.flashpunk.graphics.Emitter;
	import net.flashpunk.graphics.Graphiclist;
	import net.flashpunk.graphics.Spritemap;
	import net.flashpunk.utils.Key;
	import net.flashpunk.utils.Input;
	import net.flashpunk.FP;
	
	/**
	 * ...
	 * @author ...
	 */
	public class Background extends Entity 
	{
		[Embed(source="background.png")]
		private var BACKGROUND:Class;
		private var background:Image;
				
		public function Background(px:Number=0, py:Number=0) 
		{
			background = new Image(BACKGROUND);
			
			super(px, py, background);	
			
			this.collidable = false;
			type = "Background";							
		}
	}
}