#include"SpriteAnim.h"

/*
テクスチャのパターンアニメーション

	テクスチャアニメーション用の.cppと.hを作って実装する

	フレームカウンターを作る
	※フレームカウンター=1フレームに1繰り上がる変数

	何パターン目を再生するのか
	・表示パターン目=(フレームカウンター/待ちフレーム数)*最大パターン数			サイクルする場合
	・表示パターン目=MIN((フレームカウンター/待ちフレーム数)*最大パターン数-1)	最終フレームで止めておく場合

	テクスチャの切り取り座標x＝パターン幅	* (表示パターン目 % 横最大パターン数)
	テクスチャの切り取り座標y＝パターン高さ	* (表示パターン目 / 横最大パターン数)


	*/

