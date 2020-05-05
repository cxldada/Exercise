## 简介
使用ssh-key生成公钥后，可以使用ssh-copy-id命令将公钥自动发送到目标机器，就不用自己拷贝了

## 命令格式
`ssh-copy-id -p 端口好 username@ipaddress`

## 设置ssh的config文件

```
Host card
	Hostname 192.168.100.47
	Port 22
	User user
	IdentityFile ~/.ssh/id_rsa
	IdentitiesOnly yes
```