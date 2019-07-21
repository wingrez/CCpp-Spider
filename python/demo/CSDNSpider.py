# coding: UTF-8
from bs4 import BeautifulSoup
import urllib
import re
 
class Spider(object):
    def __init__(self):
        self.pages=[]
        self.datas=[]
        self.root="https://blog.csdn.net/wingrez"
        
    def claw(self, startpage, endpage):
        for i in range(startpage, endpage+1):
            self.pages.append(self.root+"/article/list/%d?" % i )
        for url in self.pages:
            self.getDatas(url)
            
    def download(self, url): # 下载当前网页内容
        if url is None:
            print("链接为空！")
            return None
        response=urllib.request.urlopen(url)
        if response.getcode()!=200:
            print("访问失败！")
            return None
        return response.read()
        
    def getDatas(self, url): # 获取当前页所有文章信息
        html_cont=self.download(url)
        soup=BeautifulSoup(html_cont, 'html.parser', from_encoding='UTF-8')
        articles=soup.find_all('div', class_='article-item-box csdn-tracking-statistics')
        for article in articles:
            data={}
            tag_a=article.find('h4').find('a')
            data['url']=tag_a['href']
            tag_span=tag_a.find('span')
            data['type']=tag_span.string
            data['title']=tag_span.next_element.next_element
            data['summary']=article.find('p').find('a').string
            self.datas.append(data)
            
    def output(self): # 输出数据
        fout=open('output.html','w',encoding="UTF-8")
        fout.write("<html>")
        fout.write("<body>")
        fout.write("<table>")
        for data in self.datas:
            fout.write("<tr>")
            fout.write("<td>%s</td>" % data['type'])
            fout.write("<td>%s</td>" % data['url'])
            fout.write("<td>%s</td>" % data['title'])
            fout.write("<td>%s</td>" % data['summary'])
            fout.write("</tr>")
        fout.write("</table>")
        fout.write("</body>")
        fout.write("</html>")
        fout.close()
    
if __name__=="__main__":
    spider=Spider()
    spider.claw(1,15)
    spider.output()
