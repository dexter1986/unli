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
	import net.flashpunk.Tween;
	import net.flashpunk.utils.Ease;
	
	/**
	 * ...
	 * @author ...
	 */
	public class Corazon extends Entity 
	{
		[Embed(source="corazon.png")]
		private const IMG :Class;
				
		[Embed(source="corazonAnim.png")]
		private const SPRITE :Class;
		public var sprite:Spritemap;
		
		[Embed(source="boom.mp3")]
		private const SND_Exp:Class;
		private var sfx_expl :Sfx;
		
		private var grp_List:Graphiclist;
		private var exp_Emiter:Emitter;
		
		public var isDead:Boolean = false;
		
		public function Corazon(px:Number = 0, py:Number = 0) 
		{
			sfx_expl = new Sfx(SND_Exp);
			
			exp_Emiter = new Emitter(new BitmapData(2, 2), 2,2);
			exp_Emiter.newType("explode", [0]);
			exp_Emiter.setAlpha("explode", 1, 0);
			exp_Emiter.setMotion("explode", 0, 300, 3, 360, -40,-0.5,Ease.quadOut);
			exp_Emiter.relative = false;
			
			sprite = new Spritemap(SPRITE, 76, 76);
			sprite.add("idle", [0,1,2,3,4,5,6,7,8,9], 30, true);
			sprite.add("dead", [0], 30, false);
			
			grp_List = new Graphiclist(sprite,exp_Emiter);				
			
			super(px, py, grp_List);	
			
			mask = new Pixelmask(IMG);
			type = "Corazon";
			sprite.play("idle");
				
		}
		
		override public function update():void 
		{
			if (isDead)
			{
				if (sprite.complete)
				{
					this.sprite.visible = false;
					if (exp_Emiter.particleCount == 0)
					{
						var world:GameWorld = FP.world as GameWorld;						
						world.gameReboot();
					}
				}				
			}else
			{
				if (this.collide("Bala", this.x, this.y))
				{
					die();
				}
			}
			
			super.update();
		}
		
		public function getWidth():Number
		{
			return (sprite.width / sprite.columns);
		}
		
		public function getHeight():Number
		{
			return (sprite.height / sprite.rows);
		}
		
		public function  die():void 
		{
			if (!isDead)
			{
				sfx_expl.play();
				isDead = true;
				this.collidable = false;				
				sprite.play("dead");
				exp_Emiter.setColor("explode", 0xFF0000, 0xFFFFFF);
				for (var i:uint = 0; i < 500; i++)
				{
					exp_Emiter.emit("explode", x + width / 2, y + height / 2);
				}
			}
		}
		
	}

}