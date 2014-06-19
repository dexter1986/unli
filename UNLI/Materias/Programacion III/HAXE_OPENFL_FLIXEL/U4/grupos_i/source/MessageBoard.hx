import flixel.FlxBasic;
import flixel.text.FlxText;
import flixel.FlxG;
import flixel.tweens.FlxTween;
import flixel.tweens.FlxEase;

class MessageBoard extends FlxBasic{
	private var text: FlxText;
	private var msgTime: Float = 0;


	public function new()
	{
		super();
		text = new FlxText(0, FlxG.height / 2.0, FlxG.width);
		text.visible = false;
		text.x = 0;
		text.fieldWidth = FlxG.width;
		text.alignment = "center";
		text.size = 12;
		text.visible = false;
	}

	// despliega el texto "Msg" centrado en pantalla durante "Time" segundos
	public function showMessage(Msg: String, Time: Float = 5)
	{
		msgTime = Time;
		text.text = Msg;
		text.y = FlxG.height / 2.0 - text.height / 2.0;
		text.visible = true;
		text.text = Msg;
		text.alpha = 1;
	}

	public override function update()
	{
		msgTime -= FlxG.elapsed;
		if(msgTime <= 0 && text.visible){
			FlxTween.tween(text, {"alpha": 0}, 1, {ease: FlxEase.quadOut, complete: onTweenEnd});
		}
	}

	public override function draw()
	{
		if(text.visible){
			text.draw();
		}
	}

	public function onTweenEnd(tween: FlxTween): Void
	{
		text.visible = false;
	}
}