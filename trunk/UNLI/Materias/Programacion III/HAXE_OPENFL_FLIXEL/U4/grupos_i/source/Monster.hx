import flixel.FlxSprite;
import flixel.FlxG;
import flixel.util.FlxRandom;
import flixel.tweens.FlxTween;
import flixel.tweens.FlxEase;


class Monster extends FlxSprite
{
	private var timeToMove: Float;
	private var tween: FlxTween = null;

	public function new (X: Float = 0, Y: Float = 0){
        super(X, Y);
        loadGraphic("assets/images/sprites_alpha.png", true, 16, 16);
        animation.add("moving",[32, 33], 5);
        animation.add("idle",[32], 1);
        animation.play("idle");
        newMove();
    }

    public override function update()
    {
    	super.update();
    	timeToMove -= FlxG.elapsed;
    	if(timeToMove <= 0 && tween == null){
    		var dx: Int = 0;
    		var dy: Int = 0;
    		switch (FlxRandom.intRanged(0, 3)) {
    			case 0:
    				// movimiento hacia arriba
    				dx = 0;
    				dy = -16;
    			case 1:
					// movimiento hacia abajo
    				dx = 0;
    				dy = 16;
    			case 2:
    				// movimiento hacia la derecha
    				dx = 16;
    				dy = 0;
    			case 3:
    				// movimiento hacia la izquierda
    				dx = 16;
    				dy = 0;
    		}
    		tween = FlxTween.tween(this, {"x": x + dx, "y": y + dy}, 0.5, {ease: FlxEase.quadIn, complete: onTweenEnd});
    		animation.play("moving");
    	}
    }

    private function onTweenEnd(Tween: FlxTween){
        newMove();
    	tween = null;
    	animation.play("idle");
    }

    private inline function newMove(){
        timeToMove = FlxRandom.floatRanged(0, 2);
    }
}