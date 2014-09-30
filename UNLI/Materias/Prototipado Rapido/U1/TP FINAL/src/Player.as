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
		private var _IsTrabajo:Boolean = false;
		private var _Dinero:int = 0;
		private var _IsProfesional:Boolean = false;
		private var _IsEstudio:Boolean = false;
				
		private var _contTrabajo:int = 0;
		private var _contEstudio:int = 0;
		private var _contAmor:int = 0;
		private var _contFe:int = 0;
		private var _contFamilia:int = 0;
		private var _contHijo:int = 0;
		private var _contAvaricia:int = 0;		
		private var _ageEnd:int = 1000;
		
		private var _actividad:String;		
		private var _sentimental:String;	
		private var _multTrabajo:int;
			
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
			sprite.add("anciano", [6], 1, false);
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
			_IsTrabajo = false;
			_IsProfesional = false;
			_IsEstudio = false;
			_Dinero = 0;
			_Ciclo = 0;
			_Edad = 0;
			_multTrabajo = 1;
			_contTrabajo = 3;
			_contEstudio = 0;
			_contAmor = 0;
			_contAvaricia = 0;
			_contFamilia = 3;
			_contFe = 3;
			_contHijo = 1;			
			_ageEnd = FP.rand(120);
			
			if (_ageEnd < 45)
			{
				_ageEnd = 45;
			}
			
			EvaluateAge();	
			EvaluteGrowRules();
			EvaluateRules();
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
			EvaluateRules();
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
				_estado = "anciano";
			}
			
			if (_IsEspiritu)
			{
				_estado = "espiritu";
			}
			
			sprite.play(_estado);			
		}
		//---
		
		public function IsEndSoon():Boolean
		{
			return _NextEdad >= _ageEnd;
		}
		
		//---
		public function GetNextPosX():Number
		{
			return _tempx;
		}
		
		public function GetEdad():int 
		{
			return _Edad;
		}
		
		public function GetHijo():Boolean 
		{
			return _IsHijo;
		}
		
		public function SetHijo(value:Boolean)
		{
			_IsHijo = value;
		}
		
		public function GetPareja():Boolean 
		{
			return _IsPareja;
		}
		
		public function SetPareja(value:Boolean)
		{
			_IsPareja = value;
		}
		
		public function GetTrabajo():Boolean 
		{
			return _IsTrabajo;
		}
		
		public function SetTrabajo(value:Boolean)
		{
			_IsTrabajo = value;
		}
		
		public function GetProfesional():Boolean 
		{
			return _IsProfesional;
		}
		
		public function GetEstudio():Boolean 
		{
			return _IsEstudio;
		}
		
		public function GetDinero():int 
		{
			return _Dinero;
		}
		
		public function GetNextEdad():int 
		{
			return _NextEdad;
		}
		
		public function  GetStep():int
		{
			return _step;
		}
		
		public function  GetState():String
		{
			return _estado;
		}
		
		public function GetSentimental():String 
		{
			return _sentimental;
		}
		
		public function GetActividad():String 
		{
			return _actividad;
		}
		
		override public function update():void
		{
			super.update();
		}	
		//---
		//---********************************************
		public function Divertirse():void 
		{
			if (_IsEstudio)
			{
				_contEstudio--;
				_contAmor++;
			}
			else if (_IsTrabajo)
			{
				_contTrabajo--;
				_contAmor++;
			}
		}		
		public function GotoIglesia(value:Boolean):void 
		{
			if (value)
			{
				_contFe++;
			}
			else
			{
				_contFe--;
			}
		}		
		public function JugarHijos(value:Boolean):void 
		{
			if (value)
			{
				_contHijo++;
			}else 
			{
				_contHijo--;				
			}
		}		
		public function ReunionFamilia(value:Boolean):void 
		{
			if (value)
			{
				_contFamilia++;
			}
			else
			{
				_contFamilia--;
			}
		}		
		public function Donacion(value:Boolean):void 
		{
			if (value)
			{
				_contAvaricia--;
				_Dinero -= 25;
			}
			else
			{
				_contAvaricia++;
			}
		}		
		public function Infelidad():void 
		{
			_contFamilia -= 5;			
		}	
		//---********************************************
		//---
		public function EvaluateRules():void 
		{
			if (_Edad < 5)
			{
				_actividad = "JUGANDO Y CRECIENDO";
			}
			else if(_Edad < 10)
			{
				_actividad = "ESTUDIANDO";
				_IsEstudio = true;
			}
			else if (_Edad < 25 && _IsEstudio)
			{	
				if (_contEstudio > 2)
				{
					_IsProfesional = true;
					_multTrabajo  = 2;
				}
			}
			else if(_Edad == 25 && _IsEstudio)
			{
				_IsTrabajo = true; 
				_actividad = "TRABAJANDO";
			}
			else if (_Edad < 65 )
			{				
				if (!_IsTrabajo)
				{
					_actividad = "DESEMPLEADO";	
				}
			}
			else
			{
				_IsTrabajo = false;
				_actividad = "JUBILADO";				
			}
			//---
			if (_IsEstudio)
			{
				_contEstudio++;
			}
			if (_IsTrabajo)
			{
				_Dinero += _multTrabajo * 50; 
			}
			//---
			if (_Edad < 20)
			{
				_sentimental = "NINGUNO";
			}
			if (_Edad > 20 && _Edad < 60)
			{	
				if (_contAmor > 2)
				{
					if (!_IsPareja)
					{
						if (_Edad < 50)
						{
							_sentimental = "EN PAREJA";
							_IsPareja =  true;
						}
					}
					else
					{
						
						_sentimental = "CASADO";
						if (_Edad < 45)
						{
							if (_contAmor > 4)
							{
								_sentimental = "CASADO y CON HIJOS";
								_IsHijo = true;
							}
							else
							{
								_contAmor++;
							}
						}
					}
				}				
			}			
			if (_IsPareja && _contFamilia < 1)
			{
				_sentimental = "DIVORCIADO";
				_contAmor = 0;
				_IsPareja = false;
			}
			
			if (_IsHijo && _contHijo < 1)
			{
				_IsHijo = false;
			}
			//---
						
		}
		
	}
}
