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
	public class Bala extends Entity 
	{
		[Embed(source="bala.png")]
		private const IMG :Class;
		private var img:Image;
		
		[Embed(source="boom.mp3")]
		private const SND_Exp:Class;
		private var sfx_expl :Sfx;
		
		private var exp_Emiter:Emitter;
		
		private var grp_List:Graphiclist;
		private var vel:int = 50;
		private var dirx:int = 0;
		private var diry:int = 0;				
		public var isDead:Boolean = false;
		
		public function Bala(px:Number=0, py:Number=0) 
		{
			sfx_expl = new Sfx(SND_Exp);
			
			exp_Emiter = new Emitter(new BitmapData(2, 2), 2, 2);
			exp_Emiter.newType("explode", [0]);
			exp_Emiter.setAlpha("explode", 1, 0);
			exp_Emiter.setMotion("explode", 0, 100, 1, 360, -40, -0.5);
			exp_Emiter.relative = false;
			
			img = new Image(IMG);
			
			grp_List = new Graphiclist(img,exp_Emiter);	

			super(px, py, grp_List);	
			
			mask = new Pixelmask(IMG);
			type = "Bala";	
		}
		
		public function  Init(pang:int):void 
		{
			img.angle = pang;
			
			if (pang == 0)
			{
				dirx = -1;
				x = FP.screen.width;
			}
			else if (pang == 90)
			{
				diry = 1;
				y = 0;
			}
			else if (pang == 180)
			{
				dirx = 1;
				x = 0;
			}
			else if (pang == 270)
			{
				diry = -1;
				y = FP.screen.height;
			}
			vel = FP.rand(50) + vel;
		}
		
		override public function update():void 
		{
			if (isDead)
			{	
				if (exp_Emiter.particleCount == 0)
				{
					this.destroy();				
				}								
			}
			else
			{
				x +=  vel * FP.elapsed * dirx;
				y +=  vel * FP.elapsed * diry;
				
				if (x > FP.screen.width || x < 0)
				{
					this.destroy();
				}
				
				if (y > FP.screen.height|| y < 0)
				{
					this.destroy();
				}	
				
				if (this.collide("Escudo", this.x, this.y))
				{
					die();
				}			
			}
			
			
			super.update();
		}
		
		public function destroy():void
		{			
			FP.world.remove(this);
		}	
		
		public function  die():void 
		{
			if (!isDead)
			{
				sfx_expl.play();
				isDead = true;	
				img.visible = false;
				exp_Emiter.setColor("explode", 0xFFFFFF, 0xFFFFFF);				
				for (var i:uint = 0; i < 50; i++)
				{
					exp_Emiter.emit("explode", x, y);
				}				
			}
		}		
	}
}
