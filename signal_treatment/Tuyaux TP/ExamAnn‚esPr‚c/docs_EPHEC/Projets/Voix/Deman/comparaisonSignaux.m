 function nombre = comparaisonSignaux (s,s2)    
 % *************************************************************************
 % * cette méthode compare les formants des deux mots et affiche à l'écran *
 % * si la prononciation est plus ou moins identique entre les deux mots   *
 % *************************************************************************
 % * PARAMETRES : les matrices des deux mots S et S2                        *
 % *************************************************************************
  
 %TRAITEMENT DU BRUIT
 
 attente ('Veuillez ne rien dire après avoir appuyer sur le bouton OK');
 Fs=8000;
 son=wavrecord(1*Fs,Fs,'double');
 son=son-mean(son);
 son_abs = abs (son);
 seuil=max (son_abs);
 seuil=seuil*1000;
 seuil=round (seuil);
 seuil=seuil*2;
 seuil=seuil /1000;  
 attente ('Fin du traitement du bruit');

 
 %DECOUPAGE EN SYLLABE DU PREMIER MOT 
 s = s(1:end,1);
 
 son_abs = abs (s);
 %ce qui suit va servir a isoler les syllabes du son
 son_find = find (son_abs > seuil); 
 son_find2=[];
   
 for i= 1 : length (son_find)-1
   son_find2(i)=son_find(i+1)-son_find(i);   
 end
 [c,v]=max (son_find2);
   
 ind_debut_1 = son_find(1)+1;
 ind_fin_1 = son_find(v)+1;
 ind_debut_2 = son_find(v+1)+1;
 ind_fin_2 = son_find(length(son_find));
  
 son1_1_syla = [];
 son1_1_syla = s(ind_debut_1:ind_fin_1);
 son1_2_syla = [];
 son1_2_syla = s(ind_debut_2:ind_fin_2); 
   
    
 %DECOUPAGE EN SYLLABES DU DEUXIEME MOT
   
 s2 = s2(1:end,1);       
 son_abs = abs (s);
 son_find = find (son_abs > seuil); 
 son_find2=[];
    
 for i= 1 : length (son_find)-1
   son_find2(i)=son_find(i+1)-son_find(i);   
 end
 [c,v]=max (son_find2);
   
 ind_debut_1 = son_find(1)+1;
 ind_fin_1 = son_find(v)+1;
 ind_debut_2 = son_find(v+1)+1;
 ind_fin_2 = son_find(length(son_find))+1;
   
 son2_1_syla = [];
 son2_1_syla = s2(ind_debut_1:ind_fin_1);
 son2_2_syla = [];
 son2_2_syla = s2(ind_debut_2:ind_fin_2);
   
 attente ('Fin du découpage des syllabes');
   
 %FIN DES DECOUPAGES
   
 
 %RECHERCHE DES FORMANT DES PREMIERES SYLLABYES
 [P,F,I]=formant( son1_1_syla,5);
 f_db1=zeros(length(I),1);
 freq1=zeros(length(I),1);
 [f_db1,freq1]=valeur_formant(F,I,P);
 f_db1=f_db1 * -1;
        
 [P2,F2,I2]=formant( son2_1_syla,5);   
 f_db2=zeros(length(I2),1);
 freq2=zeros(length(I2),1);
 [f_db2,freq2]=valeur_formant(F2,I2,P2);
 f_db2=f_db2 * -1; 

 %COMPARAISON
 reponse1 = [];
 reponse1 =compare(f_db1,freq1, f_db2,freq2);
                           
 %RECHERCHE DES FORMANTS DES DEUXIEMES SYLLABYES  
 [P,F,I]=formant( son1_2_syla,5);
 f_db1=zeros(length(I),1);
 freq1=zeros(length(I),1);
 [f_db1,freq1]=valeur_formant(F,I,P);
 f_db1=f_db1 * -1;
        
 [P2,F2,I2]=formant( son2_2_syla,5);   
 f_db2=zeros(length(I2),1);
 freq2=zeros(length(I2),1);
 [f_db2,freq2]=valeur_formant(F2,I2,P2);
 f_db2=f_db2 * -1;

 %COMPARAISON
 reponse2 = [];
 reponse2 = compare(f_db1,freq1, f_db2,freq2);
 
 
 %RESULTAT DE LA COMPARAISON
 %Pn va analyser les résultats obtenu pour en faire une conclusion
 reponse(1,1:5) = reponse1(1,:);
 reponse(1,6:10) = reponse2(1,:);
 reponse(2,1:5) = reponse1(2,:);
 reponse(2,6:10) = reponse2(2,:);

 calculResultat(reponse);