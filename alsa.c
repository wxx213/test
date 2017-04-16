#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h> 
 
int device_open(snd_pcm_t **pcm_handle,int mode); 
int device_setparams(snd_pcm_t *pcm_handle,snd_pcm_hw_params_t *hw_params); 
int device_capture(snd_pcm_t *pcm_handle,snd_pcm_hw_params_t *hw_params,int dtime); 
int device_play(snd_pcm_t *pcm_handle,snd_pcm_hw_params_t *hw_params);   
 
int main()
{ 
	snd_pcm_t *pcm_handle;
	snd_pcm_hw_params_t *params;
	//录音 
	if (!device_open(&pcm_handle,SND_PCM_STREAM_CAPTURE)) 
		return 1; 
	if (!device_setparams(pcm_handle,params)) 
		return 2; 
	if (!device_capture(pcm_handle,params,3)) 
		return 3; //录制3秒 
	snd_pcm_close(pcm_handle); 
	 
	//播放 
	if (!device_open(&pcm_handle,SND_PCM_STREAM_PLAYBACK)) 
		return 4; 
	if (!device_setparams(pcm_handle,params)) 
		return 5; 
	if (!device_play(pcm_handle,params)) 
		return 6; 
	snd_pcm_close(pcm_handle); 
	 
	snd_pcm_hw_params_free(params); //释放参数变量空间
	return 0; 
}  
 
int device_open(snd_pcm_t **pcm_handle,int mode)
{ 
	if (snd_pcm_open (pcm_handle, "default" , mode , 0) < 0) 
		return 0; 
	return 1; 
}
 
int device_setparams(snd_pcm_t *pcm_handle,snd_pcm_hw_params_t *hw_params) 
{ 
	unsigned int sample_feq = 44100;
	
	snd_pcm_hw_params_malloc (&hw_params); //为参数变量分配空间  
	snd_pcm_hw_params_any (pcm_handle, hw_params); //参数初始化 

	snd_pcm_hw_params_set_access (pcm_handle, hw_params,SND_PCM_ACCESS_RW_INTERLEAVED); //设置为交错模式 
	snd_pcm_hw_params_set_format(pcm_handle, hw_params,SND_PCM_FORMAT_S16_LE); //使用用16位样本 
	snd_pcm_hw_params_set_rate_near(pcm_handle, hw_params,&sample_feq, 0); //设置采样率为44.1KHz 
	snd_pcm_hw_params_set_channels(pcm_handle, hw_params, 2); //设置为立体声 
	
	snd_pcm_hw_params(pcm_handle, hw_params); //设置参数 
	return 1; 
}

int device_capture(snd_pcm_t *pcm_handle,snd_pcm_hw_params_t *hw_params,int dtime /*录音长度（单位：秒）*/)
{ 
	unsigned int rate;
	unsigned int channels; 
	snd_pcm_uframes_t period_size; //周期长度(桢数)
	int bit_per_sample; //样本长度(bit)
	snd_pcm_format_t format;
	int chunk_byte; //周期长度(字节数)
	char *wave_buf;
	int wave_buf_len;   
	int chunk_size; 
	char *data;
	snd_pcm_hw_params_get_channels(hw_params,&channels);
	snd_pcm_hw_params_get_period_size(hw_params, &period_size,0); //获取周期  
	snd_pcm_hw_params_get_format(hw_params,&format);
	if(format == SND_PCM_FORMAT_S16_LE)
		bit_per_sample = 16;
	snd_pcm_hw_params_get_rate(hw_params,&rate,0);

	//计算周期长度（字节数(bytes) = 每周期的桢数 * 样本长度(bit) * 通道数 / 8）
	chunk_byte = period_size * bit_per_sample * channels / 8;
	//计算音频数据长度（秒数 * 采样率 * 桢长度）
	wave_buf_len = dtime * rate * bit_per_sample * channels / 8; 
	 
	wave_buf = (char*)malloc(wave_buf_len); //分配空间 
	data = wave_buf;
 
	/*int r = 0; 
	while (data <= wave_buf){ 
		r = snd_pcm_readi(pcm_handle, data , chunk_size); 
		if (r>0) 
			data += r * chunk_byte;  
		else 
			return 0; 
	} */
	return 1; 
}

int device_play(snd_pcm_t *pcm_handle,snd_pcm_hw_params_t *hw_params)
{ 
	/*char *data = wave_buf; 
	int r = 0; 
	while (data <= wave_buf){ 
		r = snd_pcm_writei( pcm_handle, data , chunk_size); 
		if (r>0) 
			data += r * chunk_byte; 
		else 
			return 0; 
	} */
	return 1; 
}
