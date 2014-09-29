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
	import net.flashpunk.tweens.misc.VarTween;
	import net.flashpunk.utils.Ease;
	import net.flashpunk.tweens.misc.MultiVarTween;
		
	/**
	 * ...
	 * @author ...
	 */
	
	public class Player extends Entity 
	{	
		[Embed(source="../assets/gfx/Ciclo.png")]
		private const IMG:Class;
		
		private  var sprite:Spritemap;	
		private var grp_List:Graphiclist;
		private var scale:Number = 1;
		private var _step:int = 0;
		private var _estado:String;
		private var _Edad:int = 0;
		private var _NextEdad:int = 0;
		private var _Ciclo:int = 0;
		private var _IsPareja:Boolean = false;
		private var _IsHijo:Boolean = false;
		private var _IsEspiritu:Boolean = false;
			
		private var _tempx:Number=0;
		
		public function Player(px:Number = 0, py:Number = 0) 
		{	
		
			sprite = new Spritemap(IMG,96,96);
			sprite.add("bebe",[0], 1, false);			
			sprite.add("nino", [1], 1, false);
			sprite.add("adolescente", [2], 1, false);
			sprite.add("adulto", [3], 1, false);
			sprite.add("pareja", [4], 1, false);
			sprite.add("familia", [5], 1, false);
			sprite.add("vejez", [6], 1, false);
			sprite.add("espiritu",[7,8], 5, true);
			
			sprite.scale = scale;
			
			setHitbox(96*scale, 96*scale);
			width = 96;
			height = 96;
			
			grp_List = new Graphiclist(sprite);	
			
			super(px, py, grp_List);				
			
			type = "player";	
			
		}
		
		public function Initialize():void 
		{
			x = -15;
			y = 420;
			_step = 0;			
			_IsPareja = false;
			_IsHijo = false;
			_IsEspiritu = false;
			_Ciclo = 0;
			_Edad = 0;
			//EvaluateAge();	
			//EvaluteGrowRules();
		}
		
		public function MoveNextStep():void 
		{
			_step++;
			switch (_step) 
			{
				case 0:
					x = -15;
				break;
				case 1:
					_tempx = 215;
				break;
				case 2:
					_tempx = 470;					
				break;
				case 3:
					_tempx = 725;
				break;
				case 4:
					_tempx = 1024;
					_step = -1;
				break;
				default:
			}				
		}
		
		public function NextCicle():void 
		{
			_step = -1;
			MoveNextStep();
			
			_Ciclo++;			
			EvaluateAge();
		}
		
		public function  EvaluateAge():void 
		{
			if (_Ciclo == 0)
			{			
				_NextEdad = 1;
			}
			else if(_Ciclo == 1)			
			{
				_NextEdad = 5;
			}
			else if( _Ciclo > 1)
			{			
				_NextEdad = _Ciclo * 5 ;
			}
		}
		
		public function Grow():void 
		{
			_Edad = _NextEdad;
			EvaluteGrowRules();
		}		
		
		public function EvaluteGrowRules():void 
		{
			if (_Edad < 5)
			{
				_estado = "bebe";
			}
			else if (_Edad < 15)
			{
				_estado = "nino";
			}
			else if(_Edad < 25)
			{
				_estado = "adolescente"
			}
			else if(_Edad < 65)
			{
				if (_IsPareja)
				{
					_estado = "pareja";
				}
				else if (_IsHijo)
				{
					_estado = "familia";
				}
				else
				{
					_estado = "adulto";
				}
			}
			else
			{
				_estado = "vejez";
			}
			
			if (_IsEspiritu)
			{
				_estado = "espiritu";
			}
			
			sprite.play(_estado);			
		}
		
		public function GetNextPosX():Number
		{
			return _tempx;
		}
		
		public function GetEdad():int 
		{
			return _Edad;
		}
		
		public function  GetStep():int
		{
			return _step;
		}
		
		public function  GetState():String
		{
			return _estado;
		}
		
		override public function update():void
		{
			super.update();
		}
		
	}
}
