//
//  BiQuadFilter.mm
//  basic
//
//
//  Original Source from:
//  http://vstcpp.wpblog.jp/?page_id=728
//


#include "ofMain.h"

// --------------------------------------------------------------------------------
// BiQuadFilter
// --------------------------------------------------------------------------------
class BiQuadFilter
{
	private:
		// フィルタの係数
		float a0, a1, a2, b0, b1, b2;
		// バッファ
		float out1, out2;
		float in1, in2;

	public:
		inline BiQuadFilter();

		// 入力信号にフィルタを適用する関数
		inline float Process(float in);

		// フィルタ係数を計算するメンバー関数
		inline void LowPass  (float freq, float q , float samplerate = 44100.0f);
		inline void HighPass (float freq, float q , float samplerate = 44100.0f);
		inline void BandPass (float freq, float bw, float samplerate = 44100.0f);
		inline void Notch    (float freq, float bw, float samplerate = 44100.0f);
		inline void LowShelf (float freq, float q , float gain, float samplerate = 44100.0f);
		inline void HighShelf(float freq, float q , float gain, float samplerate = 44100.0f);
		inline void Peeking  (float freq, float bw, float gain, float samplerate = 44100.0f);
		inline void AllPass  (float freq, float q , float samplerate = 44100.0f);
};

// --------------------------------------------------------------------------------
// コンストラクタ
// --------------------------------------------------------------------------------
BiQuadFilter::BiQuadFilter() : 
	  a0(1),   a1(0), a2(0), // a0, 0以外にしておかないと除算でエラーになる
	  b0(1),   b1(0), b2(0),
	 in1(0),  in2(0), 
	out1(0), out2(0){}

// --------------------------------------------------------------------------------
// 入力信号にフィルタを適用する関数
// --------------------------------------------------------------------------------
float BiQuadFilter::Process(float in)
{
	// 入力信号にフィルタを適用し、出力信号変数に保存。
	float out = (b0 / a0 * in)   + 
		          (b1 / a0 * in1)  + 
							(b2 / a0 * in2)  - 
							(a1 / a0 * out1) - 
							(a2 / a0 * out2);

	in2 = in1; // 2つ前の入力信号を更新
	in1 = in;  // 1つ前の入力信号を更新

	out2 = out1; // 2つ前の出力信号を更新
	out1 = out;  // 1つ前の出力信号を更新

	// 出力信号を返す
	return out;
}

// --------------------------------------------------------------------------------
// フィルタ係数を計算するメンバー関数
// --------------------------------------------------------------------------------
void BiQuadFilter::LowPass(float freq, float q, float samplerate)
{
	// フィルタ係数計算で使用する中間値を求める。
	float omega = TWO_PI * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	// フィルタ係数を求める。
	a0 =  1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 =  1.0f - alpha;

	b0 = ( 1.0f - cos(omega) ) / 2.0f;
	b1 =   1.0f - cos(omega);
	b2 = ( 1.0f - cos(omega) ) / 2.0f;
}

void BiQuadFilter::HighPass(float freq, float q, float samplerate)
{
	// フィルタ係数計算で使用する中間値を求める。
	float omega = TWO_PI *  freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	// フィルタ係数を求める。
	a0 =  1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 =  1.0f - alpha;

	b0 =  ( 1.0f + cos(omega) ) / 2.0f;
	b1 = -( 1.0f + cos(omega) );
	b2 =  ( 1.0f + cos(omega) ) / 2.0f;
}

void BiQuadFilter::BandPass(float freq, float bw, float samplerate)
{
	// フィルタ係数計算で使用する中間値を求める。
	float omega = TWO_PI *  freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));

	// フィルタ係数を求める。
	a0 =  1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 =  1.0f - alpha;

	b0 =  alpha;
	b1 =  0.0f;
	b2 = -alpha;
}

void BiQuadFilter::Notch(float freq, float bw, float samplerate)
{
	// フィルタ係数計算で使用する中間値を求める。
	float omega = TWO_PI *  freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));

	// フィルタ係数を求める。
	a0 =  1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 =  1.0f - alpha;

	b0 =  1.0f;
	b1 = -2.0f * cos(omega);
	b2 =  1.0f;
}

void BiQuadFilter::LowShelf(float freq, float q, float gain, float samplerate)
{
	// フィルタ係数計算で使用する中間値を求める。
	float omega = TWO_PI *  freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);
	float A     = pow(10.0f, (gain / 40.0f));
	float beta  = sqrt(A) / q;

	// フィルタ係数を求める。
	a0 = (A + 1.0f) + (A - 1.0f) * cos(omega) + beta * sin(omega);
	a1 = -2.0f * ((A - 1.0f) + (A + 1.0f) * cos(omega));
	a2 = (A + 1.0f) + (A - 1.0f) * cos(omega) - beta * sin(omega);

	b0 = A * ((A + 1.0f) - (A - 1.0f) * cos(omega) + beta * sin(omega));
	b1 = 2.0f * A * ((A - 1.0f) - (A + 1.0f) * cos(omega));
	b2 = A * ((A + 1.0f) - (A - 1.0f) * cos(omega) - beta * sin(omega));
}

void BiQuadFilter::HighShelf(float freq, float q, float gain, float samplerate)
{
	// フィルタ係数計算で使用する中間値を求める。
	float omega = TWO_PI * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);
	float A     = pow(10.0f, (gain / 40.0f));
	float beta  = sqrt(A) / q;

	// フィルタ係数を求める。
	a0 = (A + 1.0f) - (A - 1.0f) * cos(omega) + beta * sin(omega);
	a1 = 2.0f * ((A - 1.0f) - (A + 1.0f) * cos(omega));
	a2 = (A + 1.0f) - (A - 1.0f) * cos(omega) - beta * sin(omega);

	b0 = A * ((A + 1.0f) + (A - 1.0f) * cos(omega) + beta * sin(omega));
	b1 = -2.0f * A * ((A - 1.0f) + (A + 1.0f) * cos(omega));
	b2 = A * ((A + 1.0f) + (A - 1.0f) * cos(omega) - beta * sin(omega));
}


void BiQuadFilter::Peeking(float freq, float bw, float gain, float samplerate)
{
	// フィルタ係数計算で使用する中間値を求める。
	float omega = TWO_PI * freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));
	float A     = pow(10.0f, (gain / 40.0f));

	// フィルタ係数を求める。
	a0 =  1.0f + alpha / A;
	a1 = -2.0f * cos(omega);
	a2 =  1.0f - alpha / A;

	b0 =  1.0f + alpha * A;
	b1 = -2.0f * cos(omega);
	b2 =  1.0f - alpha * A;
}

void BiQuadFilter::AllPass(float freq, float q, float samplerate)
{
	// フィルタ係数計算で使用する中間値を求める。
	float omega = TWO_PI * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	// フィルタ係数を求める。
	a0 =  1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 =  1.0f - alpha;
	b0 =  1.0f - alpha;
	b1 = -2.0f * cos(omega);
	b2 =  1.0f + alpha;
}
