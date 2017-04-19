#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h> 
#include <error.h>
 
int device_open(snd_pcm_t **pcm_handle,int mode); 
int device_setparams(snd_pcm_t *pcm_handle,snd_pcm_hw_params_t **hw_params); 
int device_capture(snd_pcm_t *pcm_handle,snd_pcm_hw_params_t *hw_params,int dtime,char **cap_data,
		int *cap_len); 
int device_play(snd_pcm_t *pcm_handle,snd_pcm_hw_params_t *hw_params,char *data,unsigned long data_len);   
 
int main()
{ 
	snd_pcm_t *pcm_handle;
	snd_pcm_hw_params_t *params;
	char *data;
	int data_len;
	//capture
	if (!device_open(&pcm_handle,SND_PCM_STREAM_CAPTURE)) 
		return 1; 
	if (!device_setparams(pcm_handle,&params)) 
		return 2; 
	if (!device_capture(pcm_handle,params,10,&data,&data_len)) 
		return 3; 
	snd_pcm_close(pcm_handle); 
	
	printf("the length of data is %d\n",data_len);
	//play
	/*if (!device_open(&pcm_handle,SND_PCM_STREAM_PLAYBACK)) 
		return 4; 
	if (!device_setparams(pcm_handle,params)) 
		return 5; 
	if (!device_play(pcm_handle,params)) 
		return 6; 
	snd_pcm_close(pcm_handle); */
	 
	snd_pcm_hw_params_free(params); 
	free(data);
	return 0; 
}  
 
int device_open(snd_pcm_t **pcm_handle,int mode)
{ 
	if (snd_pcm_open (pcm_handle, "default" , mode , 0) < 0) 
		return 0; 
	return 1; 
}
 
int device_setparams(snd_pcm_t *pcm_handle,snd_pcm_hw_params_t **hw_params) 
{ 
	unsigned int sample_feq = 44100;
	
	snd_pcm_hw_params_malloc(hw_params); //为参数变量分配空间  
	snd_pcm_hw_params_any(pcm_handle, *hw_params); //参数初始化 

	snd_pcm_hw_params_set_access(pcm_handle, *hw_params,SND_PCM_ACCESS_RW_INTERLEAVED); //设置为交错模式 
	snd_pcm_hw_params_set_format(pcm_handle, *hw_params,SND_PCM_FORMAT_S16_LE); //使用用16位样本 
	snd_pcm_hw_params_set_rate_near(pcm_handle, *hw_params,&sample_feq, 0); //设置采样率为44.1KHz 
	snd_pcm_hw_params_set_channels(pcm_handle, *hw_params, 2); //设置为立体声 
	
	snd_pcm_hw_params(pcm_handle, *hw_params); //设置参数 
	return 1; 
}

int device_capture(snd_pcm_t *pcm_handle,snd_pcm_hw_params_t *hw_params,int dtime,char **cap_data,
		int *cap_len)
{ 
	unsigned int rate;
	unsigned int channels; 
	snd_pcm_uframes_t period_size; //周期长度(桢数)
	int bit_per_sample; //样本长度(bit)
	snd_pcm_format_t format;
	int frame_byte; //frame长度(字节数)
	char *wave_buf;
	int wave_buf_len;    
	char *data;
	int data_len = 0;
	int r = 0;
	int retval;

	retval = snd_pcm_hw_params_get_channels(hw_params,&channels);
	if(retval != 0){
		printf("get channel error: %s\n",snd_strerror(retval));
		return 0;
	} 
	printf("channel is %d\n",channels);
	retval = snd_pcm_hw_params_get_period_size(hw_params, &period_size,0); //get period frames
	if(retval != 0){
		printf("get period error: %s\n",snd_strerror(retval));
		return 0;
	}  
	printf("period size is %d\n",period_size);
	snd_pcm_hw_params_get_format(hw_params,&format);
	if(format == SND_PCM_FORMAT_S16_LE)
		bit_per_sample = 16;
	printf("bit_per_sample is %d\n",bit_per_sample);
	snd_pcm_hw_params_get_rate(hw_params,&rate,0);
	printf("rate is %d\n",rate);
	frame_byte = (period_size * bit_per_sample * channels) / 8;
	//计算音频数据长度（秒数 * 采样率 * 桢长度）
	wave_buf_len = (dtime * rate * bit_per_sample * channels) / 8;
	wave_buf_len = (wave_buf_len/frame_byte + 1) * frame_byte; 
	 
	wave_buf = (char*)malloc(wave_buf_len); //分配空间 
	data = wave_buf;
 
	data_len = 0;
	while (data_len <= wave_buf_len){ 
		r = snd_pcm_readi(pcm_handle, data , 100); 
		if (r>0){ 
			data_len += r * frame_byte;
			data = wave_buf + data_len;  
		}
		else 
			return 0; 
	} 
	*cap_data = wave_buf;
	*cap_len = data_len;
	return 1; 
}

int device_play(snd_pcm_t *pcm_handle,snd_pcm_hw_params_t *hw_params,char *data,unsigned long data_len)
{ 
	 
	int r = 0; 
	while (data <= wave_buf){ 
		r = snd_pcm_writei( pcm_handle, data , chunk_size); 
		if (r>0) 
			data += r * chunk_byte; 
		else 
			return 0; 
	} 
	return 1; 
}
